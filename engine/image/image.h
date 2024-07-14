#pragma once

#include "resource/resource.h"

#include <string>

namespace Cairn {

/** An image resource. */
class Image : public Resources::Resource {

public:
  Image() : width(0), height(0), num_channels(0), pixels(nullptr) {}

  ~Image();

  /** Save the image to a file. */
  bool save(const std::string& file_path) const override;

  /** Load the image from a file. */
  bool load(const std::string& file_path) override;

  /** The width of the image. */
  int width;

  /** The height of the image. */
  int height;

  /** The number of channels in the image. */
  int num_channels;

  /** The pixel data of the image. */
  unsigned char* pixels;
};

} // namespace Cairn
