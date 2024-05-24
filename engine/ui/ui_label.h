#pragma once

#include "ui_element.h"

#include <glm/glm.hpp>

#include <string>

namespace Cairn {

/** A text label. */
class UILabel : public UIElement {

public:
  UILabel(const std::string& text, const glm::vec2& position, const glm::vec2& size)
      : UIElement(position, size), text(text) {}

  /** The font size of the text. */
  int font_size = 16;

  /** The text to display. */
  std::string text;

  float scale = 1.f;
};

} // namespace Cairn
