#pragma once

namespace Cairn {

class Texture {

public:
  Texture(const unsigned char* data, int width, int height, int num_channels)
      : data(data), width(width), height(height), num_channels(num_channels) {}

  const unsigned char* data;
  int height;
  int width;
  int num_channels;

  std::string id = "TEXTURE_ID";
};

} // namespace Cairn
