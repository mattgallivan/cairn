#include "resource.h"

#include "log/log.h"

#include <stb/stb_image.h>

#include <fstream>
#include <iostream>

namespace Cairn::Resources {

int Resource::next_id = 0;

std::string Resource::load_shader(const std::string& file_path) {
  std::ifstream file(file_path);
  if (!file.is_open()) {
    Log::error(Log::Category::Resource, "Failed to load shader file: " + file_path);
    return nullptr;
  }

  std::string shader_code;
  std::string line;
  while (std::getline(file, line)) {
    shader_code += line + "\n";
  }
  file.close();

  return shader_code;
}

Texture* Resource::load_texture(const std::string& file_path) {
  int width, height, channels;
  unsigned char* image_data = stbi_load("../resources/sprites/toast.png", &width, &height, &channels, 0);
  if (!image_data) {
    Cairn::Log::error(Cairn::Log::Category::Graphics, "Failed to load image data.");
    return nullptr;
  }

  Texture* texture = new Texture(image_data, width, height, channels);
  textures.push_back(texture);

  // TODO(matt): Leaking textures until I put in stbi_free.

  return texture;
}

} // namespace Cairn::Resources
