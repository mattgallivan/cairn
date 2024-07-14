#pragma once

#include "graphics/image.h"

#include <memory>

namespace Cairn::Resources {

class Manager {

public:
  Graphics::Image* load_image(const std::string& file_path) {
    auto image = std::make_unique<Graphics::Image>();
    image->load(file_path);
    this->images.push_back(std::move(image));
    return this->images.back().get();
  }

private:
  std::vector<std::unique_ptr<Graphics::Image>> images;
};

} // namespace Cairn::Resources