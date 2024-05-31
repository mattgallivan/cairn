#pragma once

#include <glm/glm.hpp>

namespace Cairn {

struct Color {
  Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

  float r, g, b, a;
};

static const Color Black = {0.0f, 0.0f, 0.0f, 1.0f};
static const Color White = {1.0f, 1.0f, 1.0f, 1.0f};
static const Color Red = {1.0f, 0.0f, 0.0f, 1.0f};

/** A UI element is an abstract class that represents a UI element that is drawn on the screen. */
class UIElement {

public:
  UIElement(const glm::vec2& position, const glm::vec2& size, Color color = Black)
      : position(position), size(size), color(color) {}

  virtual ~UIElement() = default;

  /** The position of the element in pixels. */
  glm::vec2 position;

  /** The size of the element in pixels. */
  glm::vec2 size;

  /** The color of the element. */
  Color color;
};

}; // namespace Cairn
