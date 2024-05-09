#pragma once

#include "sprite.h"

namespace Cairn {

class Tilemap {
public:
  Tilemap(int width, int height, int tile_width, int tile_height, Sprite* sprite)
      : width(width), height(height), tile_width(tile_width), tile_height(tile_height), sprite(sprite) {}

  int height;
  int tile_height;
  int tile_width;
  int width;

  Sprite* sprite;
};

} // namespace Cairn
