#pragma once

#include "animation.h"
#include "component.h"
#include "node.h"

#include "ecs/entity.h"
#include "ecs/system.h"
#include "graphics/graphics.h"
#include "log/log.h"

namespace Cairn::Animation {

class Renderer : public ECS::System {

public:
  Renderer(Graphics::Graphics& graphics) : graphics(graphics) {}

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

      if (const Animation* animation = animation_node->get_animation()) {
        if (const Frame* frame = animation->get_current_frame()) {
          graphics.draw(frame->image);
        }
      }
    }
  }

private:
  Graphics::Graphics& graphics;
};

} // namespace Cairn::Animation