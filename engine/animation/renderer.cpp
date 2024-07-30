#include "renderer.h"

namespace Cairn::Animation {

void Renderer::update(float delta_time_ms) {
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
        graphics.draw(frame->image, frame->x, frame->y, frame->width, frame->height);
      }
    }
  }
}

} // namespace Cairn::Animation