#pragma once

#include "ecs/entity.h"
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
 * system.update();
 * \endcode
 */
class System : public ECS::System {

public:
  void update(float delta_time_ms = 33.33f) override {
    for (auto* entity : entities) {
      auto* animation_component = entity->get_component<Cairn::Animation::Component>();
      if (!animation_component) {
        Log::error(Log::Category::Animation, "Component is invalid.");
        continue;
      }

      auto* animation_node = dynamic_cast<Cairn::Animation::AnimationNode*>(animation_component->get_node());
      if (!animation_node) {
        Log::error(Log::Category::Animation, "Node is invalid.");
        continue;
      }

      animation_node->update(delta_time_ms);
    }
  }
};

} // namespace Cairn::Animation