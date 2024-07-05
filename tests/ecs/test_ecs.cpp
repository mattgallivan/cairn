#include "engine.h"

#include <gtest/gtest.h>
#include <iostream>

namespace Cairn::ECS {

class TestComponent : public Component {
public:
  explicit TestComponent(int value) : value(value) {}
  int value;
};

class TestSystem : public System {
public:
  void update(float delta_time_ms) override {
    for (auto entity : entities) {
      auto component = entity->get_component<TestComponent>();
      if (component) {
        component->value += static_cast<int>(delta_time_ms);
      }
    }
  }
};

} // namespace Cairn::ECS

TEST(ECSTest, AddComponent) {
  Cairn::ECS::Entity entity;
  auto* component = entity.add_component<Cairn::ECS::TestComponent>(42);
  ASSERT_NE(component, nullptr);
  EXPECT_EQ(component->value, 42);
}

TEST(ECSTest, GetComponent) {
  Cairn::ECS::Entity entity;
  entity.add_component<Cairn::ECS::TestComponent>(42);
  auto* component = entity.get_component<Cairn::ECS::TestComponent>();
  ASSERT_NE(component, nullptr);
  EXPECT_EQ(component->value, 42);
}

TEST(ECSTest, RemoveComponent) {
  Cairn::ECS::Entity entity;
  entity.add_component<Cairn::ECS::TestComponent>(42);
  entity.remove_component<Cairn::ECS::TestComponent>();
  auto* component = entity.get_component<Cairn::ECS::TestComponent>();
  EXPECT_EQ(component, nullptr);
}

TEST(ECSTest, AddEntityToSystem) {
  Cairn::ECS::Entity entity;
  Cairn::ECS::TestSystem system;
  system.add_entity(&entity);
  ASSERT_EQ(system.num_entities(), 1);
}

TEST(ECSTest, RemoveEntityFromSystem) {
  Cairn::ECS::Entity entity;
  Cairn::ECS::TestSystem system;
  system.add_entity(&entity);
  system.remove_entity(&entity);
  EXPECT_EQ(system.num_entities(), 0);
}

TEST(ECSTest, SystemUpdate) {
  Cairn::ECS::Entity entity;
  auto* component = entity.add_component<Cairn::ECS::TestComponent>(42);
  Cairn::ECS::TestSystem system;
  system.add_entity(&entity);
  system.update(33.33f);
  EXPECT_EQ(component->value, 75); // 42 + 33.33 rounded down to 75
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}