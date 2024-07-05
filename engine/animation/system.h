#pragma once

#include "ecs/system.h"
#include "log/log.h"

using namespace Cairn::ECS;

namespace Cairn::Animation {

/**
 * The animation system manages all animation components and their underlying nodes.
 *
 * \code
 * Component component;
 * AnimationNode node;
 * component.set_node(&node);
 *
 * System system;
 * system.update(component);
 * \endcode
 */
class System : public ECS::System {

public:
  void update(ECS::Component& component, float delta_time_ms = 33.33f) override {
    const auto animation_component = dynamic_cast<Component*>(&component);
    if (!animation_component) {
      Log::error(Log::Category::Animation, "Component is invalid.");
      return;
    }

    const auto animation_node = dynamic_cast<AnimationNode*>(animation_component->get_node());
    if (!animation_node) {
      Log::error(Log::Category::Animation, "Node is invalid.");
      return;
    }

    animation_node->update(delta_time_ms);
  }
};

} // namespace Cairn::Animation