#include <gtest/gtest.h>

#include "memory/buffer.h"
#include "time/ttime.h"

namespace Cairn {

class TimeTest : public ::testing::Test {
protected:
  Byte data[40];
  Buffer buffer;

  TimeTest() : buffer(data, sizeof(data)) {}

  virtual void SetUp() {
    for (size_t i = 0; i < sizeof(data); i++) {
      data[i] = 0;
    }
  }
};

TEST_F(TimeTest, FormatsTimeCorrectly) {
  Time::get_current_time(buffer);
  int dash_count = 0;
  int colon_count = 0;
  for (size_t i = 0; i < buffer.size && buffer.data[i] != '\0'; i++) {
    if (buffer.data[i] == ':')
      colon_count++;
  }
  ASSERT_EQ(colon_count, 2);
}

} // namespace Cairn

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
