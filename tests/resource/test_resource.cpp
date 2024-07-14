#include "engine.h"

#include <gtest/gtest.h>

using namespace Cairn::Resources;

// Test fixture for Resource class
class ResourceTest : public ::testing::Test {
protected:
  void SetUp() override {
    // Reset next_id before each test to ensure consistent test results
    Resource::reset_next_id();
  }
};

// Mock class to test the abstract Resource class
class MockResource : public Resource {
public:
  using Resource::get_id; // Expose get_id() method for testing
};

// Test that the ID of a newly created Resource is 0
TEST_F(ResourceTest, InitialID) {
  MockResource res;
  EXPECT_EQ(res.get_id(), 0);
}

// Test that the ID of multiple resources increments correctly
TEST_F(ResourceTest, IncrementingID) {
  MockResource res1;
  MockResource res2;
  MockResource res3;

  EXPECT_EQ(res1.get_id(), 0);
  EXPECT_EQ(res2.get_id(), 1);
  EXPECT_EQ(res3.get_id(), 2);
}

// Test that next_id is shared across all instances
TEST_F(ResourceTest, SharedNextID) {
  MockResource res1;
  MockResource res2;

  EXPECT_EQ(res1.get_id(), 0);
  EXPECT_EQ(res2.get_id(), 1);

  MockResource res3;
  EXPECT_EQ(res3.get_id(), 2);
}