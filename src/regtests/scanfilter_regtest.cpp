#include <gtest/gtest.h>
#include <memory/buffer_pool.h>
#include <tasking/tasking.h>
#include <omp.h>
#include <numa.h>
#include <chrono>

SMILE_NS_BEGIN

#define PAGE_SIZE_KB 64
#define DATA_KB 4*1024*1024
#define NUM_THREADS 1

inline void run(BufferPool& bufferPool) {
		uint64_t threshold = 2^32/2;
		uint64_t counter = 0;
    constexpr int32_t PADDING_FACTOR=16;
		std::array<uint32_t,NUM_THREADS*PADDING_FACTOR> partialCounter;
		const uint64_t numaNodes = numa_max_node() + 1;
		//ASSERT_TRUE(NUM_THREADS >= numaNodes && NUM_THREADS % numaNodes == 0);

		// Scan Filter operation
		#pragma omp parallel num_threads(NUM_THREADS)
		{
			uint64_t threadID = omp_get_thread_num();
			uint64_t numThreads = omp_get_num_threads();
			uint64_t numPages = DATA_KB / PAGE_SIZE_KB;
			uint64_t startingPage = threadID;
			BufferHandler bufferHandler;


			for (uint64_t i = startingPage; i < numPages; i += numThreads) {
				uint64_t page = i;

        if(!bufferPool.isProtected(page)) {
          bufferPool.pin(page, &bufferHandler);

          uint32_t* buffer = reinterpret_cast<uint32_t*>(bufferHandler.m_buffer);
          for (uint64_t byte = 0; byte < PAGE_SIZE_KB*1024; byte += 4) {
            uint32_t number = *buffer;
            if (number > threshold)  {
              ++partialCounter[threadID*PADDING_FACTOR];
            }
            ++buffer;
          }

          bufferPool.unpin(bufferHandler.m_pId);
        }
			}
		}
		#pragma omp barrier

		// Final aggregate
		for (uint64_t i = 1; i < NUM_THREADS; ++i) {
			counter += partialCounter[i];
		}
}

/**
 * Tests a scan operation which filters the values found in a set of pages for benchmarking purposes.
 */
TEST(PerformanceTest, PerformanceTestScanFilter) {
	if (std::ifstream("./test.db")) {
		startThreadPool(0);

		BufferPool bufferPool;
		BufferPoolConfig bpConfig;
		bpConfig.m_poolSizeKB = 1024*1024;
		bpConfig.m_prefetchingDegree = 0;
		bpConfig.m_numberOfPartitions = 128;
		ASSERT_TRUE(bufferPool.open(bpConfig, "./test.db") == ErrorCode::E_NO_ERROR);

    int num_iters= 10;
    run(bufferPool);
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < num_iters; ++i) {
      run(bufferPool);
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Execution time: " << std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count() << std::endl;

		stopThreadPool();
    	bufferPool.close();
	}
}

SMILE_NS_END

int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc,argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}
