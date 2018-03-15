#include <gtest/gtest.h>
#include <memory/buffer_pool.h>

SMILE_NS_BEGIN

/**
 * 
 */
TEST(RegressionTest, RegressionTestScan) {
  BufferPool bufferPool;
  ASSERT_TRUE(bufferPool.create(BufferPoolConfig{64*8192}, "./test.db", FileStorageConfig{4}, true) == ErrorCode::E_NO_ERROR);
  BufferHandler bufferHandler;

  ASSERT_TRUE(bufferPool.alloc(&bufferHandler) == ErrorCode::E_NO_ERROR);
}

SMILE_NS_END

int main(int argc, char* argv[]){
  ::testing::InitGoogleTest(&argc,argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}