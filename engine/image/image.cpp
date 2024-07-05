#include "image.h"

#include "log/log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <filesystem>

using Cairn::Log;

namespace Cairn {

Image::~Image() {
  if (pixels) {
    stbi_image_free(pixels);
  }
}

bool Image::save(const std::string& file_path) const {
  if (!pixels) {
    Log::error(Log::Category::Resource, std::string("No image data to save for: ") + file_path);
    return false;
  }

  int success = 0;
  std::string extension = std::filesystem::path(file_path).extension().string();

  if (extension == ".png") {
    success = stbi_write_png(file_path.c_str(), width, height, num_channels, pixels, width * num_channels);
  } else if (extension == ".jpg" || extension == ".jpeg") {
    int quality = 100;
    success = stbi_write_jpg(file_path.c_str(), width, height, num_channels, pixels, quality);
  } else if (extension == ".bmp") {
    success = stbi_write_bmp(file_path.c_str(), width, height, num_channels, pixels);
  } else {
    Log::error(Log::Category::Resource, "Unsupported file format for saving: " + file_path);
    return false;
  }

  if (!success) {
    Log::error(Log::Category::Resource, "Failed to save image: " + file_path);
    return false;
  }

  return true;
}

bool Image::load(const std::string& file_path) {
  state = State::Loading;
  pixels = stbi_load(file_path.c_str(), &width, &height, &num_channels, 0);

  if (!pixels) {
    Log::error(Log::Category::Resource, std::string("Failed to load image: ") + file_path);
    state = State::Failed;
    return false;
  }

  state = State::Loaded;
  return true;
}

} // namespace Cairn
