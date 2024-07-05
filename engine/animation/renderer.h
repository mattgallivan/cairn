#pragma once

#include "animation.h"
#include "component.h"
#include "node.h"

#include "graphics/graphics.h"

#include <iostream>

namespace Cairn::Animation {

class Renderer {

public:
  Renderer(Graphics::Graphics& graphics) : graphics(graphics) {}

  void render(Component& component) const {
    // Animation Node
    if (const auto animation_node = dynamic_cast<AnimationNode*>(component.get_node())) {
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