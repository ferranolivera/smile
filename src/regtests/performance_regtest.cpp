#include <gtest/gtest.h>
#include <memory/buffer_pool.h>

SMILE_NS_BEGIN
/**
 * Tests an alloc operation of 4GB over a 1GB-size Buffer Pool for benchmarking purposes.
 */
TEST(PerformanceTest, PerformanceTestAlloc) {
	BufferPool bufferPool;
	ASSERT_TRUE(bufferPool.create(BufferPoolConfig{1024*1024}, "./test.db", FileStorageConfig{64}, true) == ErrorCode::E_NO_ERROR);
	BufferHandler bufferHandler;

	double duration;
	std::clock_t start = std::clock();

	for (uint64_t i = 0; i < 4*1024*1024; i += 64) {
		ASSERT_TRUE(bufferPool.alloc(&bufferHandler) == ErrorCode::E_NO_ERROR);
		ASSERT_TRUE(bufferPool.unpin(bufferHandler.m_pId) == ErrorCode::E_NO_ERROR);
	}

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "alloc_regtest = " << duration << std::endl;
}

/**
 * Tests a scan operation of 4GB over a 1GB-size Buffer Pool for benchmarking purposes.
 */
TEST(PerformanceTest, PerformanceTestScan) {
	BufferPool bufferPool;
	ASSERT_TRUE(bufferPool.create(BufferPoolConfig{1024*1024}, "./test.db", FileStorageConfig{64}, true) == ErrorCode::E_NO_ERROR);
	BufferHandler bufferHandler;

	std::vector<pageId_t> pages;

	// Allocate 4GB in disk before proceed scanning.
	for (uint64_t i = 0; i < 4*1024*1024; i += 64) {
		ASSERT_TRUE(bufferPool.alloc(&bufferHandler) == ErrorCode::E_NO_ERROR);
		ASSERT_TRUE(bufferPool.unpin(bufferHandler.m_pId) == ErrorCode::E_NO_ERROR);
		pages.push_back(bufferHandler.m_pId);
	}

	double duration;
	std::clock_t start = std::clock();

	for (uint64_t i = 0; i < 4*1024*1024; i += 64) {
		ASSERT_TRUE(bufferPool.pin(pages[i/64], &bufferHandler) == ErrorCode::E_NO_ERROR);
		ASSERT_TRUE(bufferPool.setPageDirty(bufferHandler.m_pId) == ErrorCode::E_NO_ERROR);
		uint64_t dataToWrite = i;
		memcpy(bufferHandler.m_buffer, &dataToWrite, sizeof(uint64_t));
		ASSERT_TRUE(bufferPool.unpin(bufferHandler.m_pId) == ErrorCode::E_NO_ERROR);
	}

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	std::cout << "scan_regtest = " << duration << std::endl;
}

SMILE_NS_END

int main(int argc, char* argv[]){
	::testing::InitGoogleTest(&argc,argv);
	int ret = RUN_ALL_TESTS();
	return ret;
}
