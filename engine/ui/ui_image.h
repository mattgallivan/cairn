#pragma once

#include "ui_element.h"

#include <string>

namespace Cairn {

  class UIImage : public UIElement {
    
  public:
    UIImage(const glm::vec2& position, const glm::vec2& size, const std::vector<unsigned char>& data, int width, int height, int num_channels) : UIElement(position, size), data(data), width(width), height(height), num_channels(num_channels) {}

    std::vector<unsigned char> data;
		int width;
		int height;
		int num_channels;

  };
  
} // namespace Cairn
