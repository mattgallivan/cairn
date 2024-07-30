#include "image.h"

#include "log/log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

#include <filesystem>

using Cairn::Log;

namespace Cairn::Graphics {

Image::~Image() {
  if (pixels) {
    stbi_image_free(pixels);
  }
}

std::string Image::serialize() const {
  if (!pixels) {
    Log::error(Log::Category::Resource, "No image data to serialize.");
    return std::string();
  }

  return std::string(reinterpret_cast<const char*>(pixels), width * height * num_channels);
}

bool Image::deserialize(const std::string& data) {
  stbi_image_free(pixels);
  stbi_load_from_memory(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), &width, &height,
                        &num_channels, 0);
  return pixels != nullptr;
}

} // namespace Cairn::Graphics
