#include "memory/memory.h"
#include <gtest/gtest.h>

class StackAllocatorTest : public ::testing::Test {
protected:
  Cairn::StackAllocator* allocator;
  static const Cairn::Size test_stack_size = 1024;

  void SetUp() override {
    allocator = new Cairn::StackAllocator(test_stack_size);
  }

  void TearDown() override { delete allocator; }
};

TEST_F(StackAllocatorTest, AllocateSmallBlock) {
  void* block = allocator->allocate(16);
  EXPECT_NE(block, nullptr);
}

TEST_F(StackAllocatorTest, AllocateOverflow) {
  void* block = allocator->allocate(test_stack_size + 1);
  EXPECT_EQ(block, nullptr);
}

TEST_F(StackAllocatorTest, MultipleAllocations) {
  void* first_block = allocator->allocate(16);
  void* second_block = allocator->allocate(32);
  EXPECT_NE(first_block, nullptr);
  EXPECT_NE(second_block, nullptr);
  EXPECT_GE(static_cast<char*>(second_block) - static_cast<char*>(first_block),
            16);
}

TEST_F(StackAllocatorTest, Reset) {
  void* first_block = allocator->allocate(16);
  allocator->reset();
  void* second_block = allocator->allocate(16);
  EXPECT_EQ(first_block, second_block);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
