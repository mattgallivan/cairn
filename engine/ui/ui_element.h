#pragma once

#include <glm/glm.hpp>

namespace Cairn {

/** A UI element is an abstract class that represents a UI element that is drawn on the screen. */
class UIElement {

public:
  UIElement(const glm::vec2& position, const glm::vec2& size) : position(position), size(size) {}

  virtual ~UIElement() = default;

  /** The position of the element in pixels. */
  glm::vec2 position;

  /** The size of the element in pixels. */
  glm::vec2 size;
};

}; // namespace Cairn
