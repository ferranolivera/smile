

#ifndef _TASKING_TASK_H_
#define _TASKING_TASK_H_ value

#include "../base/platform.h"



SMILE_NS_BEGIN

class SyncCounter;

typedef void(*TaskFunction)(void *arg);  

struct Task {
  /**
   * @brief Pointer to the function that executed the task
   */
  TaskFunction  p_fp = nullptr;

  /**
   * @brief Pointer to the argument data that will be passed to the task
   * function
   */
  void*         p_args = nullptr;
};



SMILE_NS_END

#endif /* ifndef _TASKING_TASK_H_ */
