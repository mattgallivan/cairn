#pragma once

#include <vector>

namespace Cairn {

/** A texture is a 2D image that can be used to render a sprite. */
class Texture {

public:
  Texture(const unsigned char* data, int width, int height, int num_channels)
      : data(data), width(width), height(height), num_channels(num_channels) {
    static unsigned int counter = 0;
    id = "Texture_" + std::to_string(counter++);
  }

  /** The image data of the texture. */
  const unsigned char* data;

  /** The height of the texture in pixels. */
  int height;

  /** The width of the texture in pixels. */
  int width;

  /** The number of channels in the texture. */
  int num_channels;

  /** The unique identifier of the texture. */
  std::string id;
};

/** A texture atlas is a collection of textures that are all stored in a single image. */
class TextureAtlas : public Texture {

public:
  TextureAtlas(const unsigned char* data, int width, int height, int num_channels, int tile_width, int tile_height)
      : Texture(data, width, height, num_channels), tile_width(tile_width), tile_height(tile_height) {
    for (int y = 0; y < height; y += tile_height) {
      for (int x = 0; x < width; x += tile_width) {
        textures.push_back(new Texture(data + (y * width + x) * num_channels, tile_width, tile_height, num_channels));
      }
    }
  }

  ~TextureAtlas() {
    for (Texture* texture : textures) {
      delete texture;
    }
  }

  TextureAtlas(const TextureAtlas&) = delete;

  TextureAtlas& operator=(const TextureAtlas&) = delete;

  TextureAtlas(TextureAtlas&&) = delete;

  /** Get the texture at the specified index. */
  Texture* get_texture(int index) { return textures[index]; }

  /** The width of each tile in the texture atlas. */
  int tile_width;

  /** The height of each tile in the texture atlas. */
  int tile_height;

private:
  /** The textures in the texture atlas. */
  std::vector<Texture*> textures;
};

} // namespace Cairn
