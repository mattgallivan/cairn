#pragma once

#include "graphics/image.h"
#include "graphics/spritesheet.h"

#include <memory>
#include <string>
#include <vector>

namespace Cairn::Resources {

class Manager {

public:
  Graphics::Image* load_image(const std::string& file_path) {
    auto image = std::make_unique<Graphics::Image>();
    image->load(file_path);
    images.push_back(std::move(image));
    return images.back().get();
  }

  Graphics::Spritesheet* load_spritesheet(const std::string& file_path) {
    auto spritesheet = std::make_unique<Graphics::Spritesheet>();
    // spritesheet->load(file_path);
    spritesheets.push_back(std::move(spritesheet));
    return spritesheets.back().get();
  }

private:
  std::vector<std::unique_ptr<Graphics::Image>> images;

  std::vector<std::unique_ptr<Graphics::Spritesheet>> spritesheets;
};

} // namespace Cairn::Resources