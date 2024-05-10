#pragma once

#include "sprite.h"

namespace Cairn {

class Tilemap {
public:
  Tilemap(int width, int height, int tile_width, int tile_height, std::vector<Sprite> sprites, std::vector<int> data)
      : width(width), height(height), tile_width(tile_width), tile_height(tile_height), sprites(sprites), data(data) {}

  Sprite get_sprite(int x, int y) {
    int index = data[y * width + x];
    return sprites[index];
  }

  int height;
  int tile_height;
  int tile_width;
  int width;

  std::vector<Sprite> sprites;
  std::vector<int> data;

  glm::vec2 position = glm::vec2(0.0f, 0.0f);
};

} // namespace Cairn
