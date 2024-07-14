#include "system.h"

#include "component.h"
#include "ecs/entity.h"
#include "log/log.h"
#include "node.h"

namespace Cairn::Animation {

void System::update(float delta_time_ms) {
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

} // namespace Cairn::Animation