#pragma once

#include "ecs/system.h"
#include "image/image.h"

#include <memory>

namespace Cairn::Resources {

class System : ECS::System {

public:
  void update(float delta_time_ms = 33.33f) override {}

  Image* load_image(const std::string& file_path) {
    auto image = std::make_unique<Image>();
    image->load(file_path);
    this->images.push_back(std::move(image));
    return this->images.back().get();
  }

private:
  std::vector<std::unique_ptr<Image>> images;
};

} // namespace Cairn::Resources