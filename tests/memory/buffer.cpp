#include <gtest/gtest.h>

#include "buffer.h"

namespace Cairn {

class BufferTest : public ::testing::Test {
protected:
  Byte data[100];

  virtual void SetUp() {
    for (int i = 0; i < 100; i++) {
      data[i] = 'a';
    }
  }
};

TEST_F(BufferTest, HoldsCorrectPointer) {
  Buffer buffer(data, 100);
  ASSERT_EQ(buffer.data, data);
}

TEST_F(BufferTest, ReportsCorrectSize) {
  Buffer buffer(data, 100);
  ASSERT_EQ(buffer.size, 100);
}

} // namespace Cairn

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
