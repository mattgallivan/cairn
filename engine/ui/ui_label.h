#pragma once

#include "ui_element.h"

#include <glm/glm.hpp>

#include <string>

namespace Cairn {

/** A text label. */
class UILabel : public UIElement {

public:
  UILabel(const std::string& text, const glm::vec2& position, const glm::vec2& size, Color color = White)
      : UIElement(position, size, color), text(text) {}

  /** The font size of the text. */
  int font_size = 16;

  /** The text to display. */
  std::string text;

  float scale = 1.f;
};

} // namespace Cairn
