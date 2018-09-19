
#include "sync_counter.h"
#include "task_pool.h"
#include "tasking.h"

#include <atomic>
#include <boost/context/continuation.hpp>
#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace ctx = boost::context;
using ExecutionContext = ctx::continuation;

SMILE_NS_BEGIN

/**
 * @brief  Structure used to represent a task to be executed by the thread pool
 */
struct TaskContext {

  /**
   * @brief Task encapsulated within this task context
   */
  Task              m_task;

  /**
   * @brief Synchronization counter used to synchronize this task
   */
  SyncCounter*      p_syncCounter = nullptr;

  /**
   * @bried The execution context of this task
   */
  ExecutionContext  m_context;

  /**
   * @brief Whether the task is finished or not
   */
  bool              m_finished  = false;

  /**
   * @brief A pointer to the parent of the task in the task dependency graph
   */
  TaskContext*      p_parent;

};  


static bool                         m_initialized = false;

/**
 * @brief Atomic booleans to control threads running
 */
static std::atomic<bool>*           m_isRunning = nullptr;;

/**
 * @brief The number of threads in the thread pool
 */
static std::size_t                  m_numThreads = 0;

/**
 * @brief Vector of running threads objects
 */
static std::thread**                p_threads;

/**
 * @brief Pointer to the task pool with the tasks pending to start 
 */
static TaskPool*                    p_toStartTaskPool = nullptr;

/**
 * @brief Vectors holding the running tasks of the thread.
 */
static TaskPool*                    p_runningTaskPool = nullptr;


/**
 * @brief Thread local variable to store the id of the current thread
 */
static thread_local uint32_t        m_currentThreadId = INVALID_THREAD_ID;

/**
 * @brief Array of Contexts used to store the main context of each thread to
 * fall back to it when yielding a task
 */
static ExecutionContext*            m_threadMainContexts = nullptr;

/**
 * @brief Mutexes used for the condition variables for notifying sleeping
 * threads that more work is ready
 */
static std::mutex*                  m_condVarMutexes = nullptr;


/**
 * @brief Condition variables sed to notify sleeping threads that more work is
 * ready
 */
static std::condition_variable*     m_condVars = nullptr;
/**
 * @brief Boolean flag used for condition variables for notifying sleepting
 * threads that more work is ready
 */
static bool*                        m_ready = nullptr;

/**
 * @brief Pointer to the thread local currently running task 
 */
static thread_local TaskContext*    p_currentRunningTask = nullptr;

/**
 * @brief Finalizes the current running task and releases its resources
 */
static void finalizeCurrentRunningTask() {
  if(p_currentRunningTask->m_finished) {
    if(p_currentRunningTask->p_syncCounter != nullptr) {
      int32_t last = p_currentRunningTask->p_syncCounter->fetch_decrement();
    }
    delete p_currentRunningTask; // TODO: If a pool is used, reset the task and put it into the pool
  } else {
    p_runningTaskPool->addTask(m_currentThreadId, p_currentRunningTask);
  }
  p_currentRunningTask = nullptr;
}

/**
 * @brief Start the execution of the given task. A lambda function is passed
 * to the callcc method, which takes as input the current execution context.
 * This current execution context is stored int he m_threadMainContexts array
 * for the current thread. Then the task is executed. 
 *
 * @param task The task to execute
 */
static void startTask(TaskContext* taskContext) noexcept {
  p_currentRunningTask = taskContext; // TODO: A pool should be used here
  p_currentRunningTask->m_context = ctx::callcc([taskContext](ExecutionContext&& context) {
              m_threadMainContexts[m_currentThreadId] = std::move(context);
              taskContext->m_task.p_fp(taskContext->m_task.p_args);
              p_currentRunningTask->m_finished  = true;
              return std::move(m_threadMainContexts[m_currentThreadId]);
              }
             );
  finalizeCurrentRunningTask();
}


/**
 * @brief Resumes the given running task 
 *
 * @param runningTask The task to resume
 */
static void resumeTask(TaskContext* runningTask) {
  p_currentRunningTask = runningTask;
  p_currentRunningTask->m_context = p_currentRunningTask->m_context.resume();
  finalizeCurrentRunningTask();
}

/**
 * @brief The main function that each thread runs
 *
 * @param threadId The id of the thread that runs the function
 */
static void threadFunction(int threadId) noexcept {

  m_currentThreadId = threadId;

  while(m_isRunning[m_currentThreadId].load()) {
    TaskContext* task = p_toStartTaskPool->getNextTask(m_currentThreadId);
    if(task != nullptr) {
      startTask(task);
    } else if ( (task = p_runningTaskPool->getNextTask(m_currentThreadId)) != nullptr) {
      resumeTask(task);
    } else {
      // Wait until notified
      std::unique_lock<std::mutex> lock(m_condVarMutexes[m_currentThreadId]);
      m_ready[m_currentThreadId] = false;
      m_condVars[m_currentThreadId].wait_for(lock,
                                             std::chrono::milliseconds(1), 
                                             [] { return m_ready[m_currentThreadId]; });
    }
  }
}

void startThreadPool(std::size_t numThreads) noexcept {

  m_numThreads          = numThreads;

  if(m_numThreads > 0) {
    p_toStartTaskPool     = new TaskPool{numThreads};
    p_runningTaskPool     = new TaskPool{numThreads};
    m_threadMainContexts  = new ExecutionContext[numThreads];
    m_isRunning           = new std::atomic<bool>[m_numThreads];
    p_threads             = new std::thread*[m_numThreads];
    m_condVarMutexes      = new std::mutex[m_numThreads];
    m_condVars            = new std::condition_variable[m_numThreads];
    m_ready               = new bool[m_numThreads];

    for(std::size_t i = 0; i < m_numThreads; ++i) {
      m_isRunning[i].store(true);
      p_threads[i] = new std::thread(threadFunction, i);
      m_ready[i] = false;
    }
  }
  m_initialized = true;

}

void stopThreadPool() noexcept {
  assert(m_initialized && "ThreadPool is not initialized");

  if(m_numThreads > 0) {
    // Telling threads to stop
    for(std::size_t i = 0; i < m_numThreads; ++i) {
      m_isRunning[i].store(false);
    }

    // Notify threads to continue
    for(std::size_t i = 0; i < m_numThreads; ++i) {
      {
        std::lock_guard<std::mutex> guard(m_condVarMutexes[i]);
        m_ready[i] = true;
      }
      m_condVars[i].notify_all();
    }

    // Waitning threads to stop
    for(std::size_t i = 0; i < m_numThreads; ++i) {
      p_threads[i]->join();
      delete p_threads[i];
    }

    delete [] m_ready;
    delete [] m_condVars;
    delete [] m_condVarMutexes;
    delete [] p_threads;
    delete [] m_isRunning;
    delete [] m_threadMainContexts;
    delete p_runningTaskPool;
    delete p_toStartTaskPool;
  }
  m_initialized = false;
}

void executeTaskAsync(uint32_t queueId, Task task, SyncCounter* counter ) noexcept {
  assert(m_initialized && "ThreadPool is not initialized");
  assert(m_numThreads > 0 && "Number of threads in the threadpool must be > 0");
  TaskContext* taskContext = new TaskContext{task, counter};
  if(taskContext->p_syncCounter != nullptr) {
    taskContext->p_syncCounter->fetch_increment();
  }

  if(getCurrentThreadId() != INVALID_THREAD_ID ) {
    taskContext->p_parent = p_currentRunningTask;
  } else {
    taskContext->p_parent = nullptr;
  }

  p_toStartTaskPool->addTask(queueId, taskContext);

  {
    std::lock_guard<std::mutex> guard(m_condVarMutexes[queueId]);
    m_ready[queueId] = true;
  }
  m_condVars[queueId].notify_all();
} 

void executeTaskSync(uint32_t queueId, 
                     Task task, 
                     SyncCounter* counter) noexcept {
  assert(m_initialized && "ThreadPool is not initialized");
  assert(m_numThreads > 0 && "Number of threads in the threadpool must be > 0");
  executeTaskAsync(queueId, task, counter);
  counter->join();
}

uint32_t getCurrentThreadId() noexcept {
  return m_currentThreadId;
}

void yield() {
  assert(m_initialized && "ThreadPool is not initialized");
  assert(m_numThreads > 0 && "Number of threads in the threadpool must be > 0");
  assert(m_currentThreadId != INVALID_THREAD_ID);
  m_threadMainContexts[m_currentThreadId] = m_threadMainContexts[m_currentThreadId].resume();
}

std::size_t getNumThreads() noexcept {
  assert(m_initialized && "ThreadPool is not initialized");
  return m_numThreads;
}

SMILE_NS_END
