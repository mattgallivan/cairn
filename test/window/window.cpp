#include <gtest/gtest.h>

#include "window/window.h"

TEST(WindowTest, CanInstantiateWindow) {
  ASSERT_NO_THROW({ Cairn::Window window(800, 600, "My First Window"); });
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
