#pragma once

#include <vector>

namespace Cairn {

class Texture {

public:
  Texture(const unsigned char* data, int width, int height, int num_channels)
      : data(data), width(width), height(height), num_channels(num_channels) {
    static unsigned int counter = 0;
    id = "Texture_" + std::to_string(counter++);
  }

  const unsigned char* data;
  int height;
  int width;
  int num_channels;

  std::string id;
};

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

  // TODO(matt): Add the remaining constructors and destructors.

  Texture* get_texture(int index) { return textures[index]; }

  int tile_width;
  int tile_height;

private:
  std::vector<Texture*> textures;
};

} // namespace Cairn
