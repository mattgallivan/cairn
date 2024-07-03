#pragma once

#include "log/log.h"
#include "texture.h"

#include <glm/glm.hpp>

#include <vector>

namespace Cairn {

/** A tilemap is a grid of tiles that can be rendered to the screen. Each tile is a texture from a texture atlas. */
class Tilemap {
public:
  Tilemap(int width,
          int height,
          int tile_width,
          int tile_height,
          TextureAtlas* atlas,
          const std::vector<int>& data,
          glm::vec2 position = glm::vec2(0.0f, 0.0f))
      : width(width), height(height), tile_width(tile_width), tile_height(tile_height), atlas(atlas), data(data),
        position(position) {
    if (width <= 0 || height <= 0) {
      Log::error(Log::Category::Graphics, "Tilemap width and height must be greater than 0.");
    }

    if (tile_width <= 0 || tile_height <= 0) {
      Log::error(Log::Category::Graphics, "Tile width and height must be greater than 0.");
    }

    if (width * height != data.size()) {
      Log::error(Log::Category::Graphics, "Tilemap data size does not match width and height.");
    }

    if (!atlas) {
      Log::error(Log::Category::Graphics, "Texture atlas is null.");
    }
  }

  /** The height of the tilemap in tiles. */
  int height;

  /** The width of the tilemap in tiles. */
  int width;

  /** The height of each tile in pixels. */
  int tile_height;

  /** The width of each tile in pixels. */
  int tile_width;

  /** The texture atlas containing the tile textures. */
  TextureAtlas* atlas;

  /** The tile data. Each integer is an index into the texture atlas. */
  const std::vector<int>& data;

  /** The position of the top-left of the tilemap in world space. */
  glm::vec2 position;
};

} // namespace Cairn
