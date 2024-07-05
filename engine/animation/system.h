#pragma once

#include "ecs/system.h"
#include "log/log.h"

using namespace Cairn::ECS;

namespace Cairn::Animation {

class System : public ECS::System {

public:
  void update(ECS::Component& component, float delta_time_ms) override {
    auto animation_component = dynamic_cast<Component*>(&component);
    if (!animation_component) {
      Log::error(Log::Category::Animation, "Component is not an animation component.");
      return;
    }

    // Animation Node
    if (const auto animation_node = dynamic_cast<AnimationNode*>(animation_component->get_node())) {
      if (auto animation = animation_node->get_animation()) {
        animation_node->update(delta_time_ms);
      }
    }
  }
};

} // namespace Cairn::Animation