#pragma once

#include "sprite.h"

namespace Cairn {

class Tilemap {
public:
  Tilemap(int width, int height, int tile_width, int tile_height, TextureAtlas* atlas, std::vector<int> data)
      : width(width), height(height), tile_width(tile_width), tile_height(tile_height), atlas(atlas), data(data) {}

  int height;
  int tile_height;
  int tile_width;
  int width;

  TextureAtlas* atlas;
  std::vector<int> data;

  glm::vec2 position = glm::vec2(0.0f, 0.0f);
};

} // namespace Cairn
