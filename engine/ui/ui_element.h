#pragma once

#include <glm/glm.hpp>

namespace Cairn {

struct Color {
  /** Construct a color with the default RGBA values (black). */
  Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

  /** Construct a color with the given RGBA values. */
  Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

  float r, g, b, a;
};

// Predefined colors.
static const Color Black = {0.0f, 0.0f, 0.0f, 1.0f};
static const Color White = {1.0f, 1.0f, 1.0f, 1.0f};
static const Color Red = {1.0f, 0.0f, 0.0f, 1.0f};
static const Color Green = {0.0f, 1.0f, 0.0f, 1.0f};
static const Color Blue = {0.0f, 0.0f, 1.0f, 1.0f};
static const Color Yellow = {1.0f, 1.0f, 0.0f, 1.0f};
static const Color Cyan = {0.0f, 1.0f, 1.0f, 1.0f};
static const Color Magenta = {1.0f, 0.0f, 1.0f, 1.0f};
static const Color Gray = {0.5f, 0.5f, 0.5f, 1.0f};

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
