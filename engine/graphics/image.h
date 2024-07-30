#pragma once

#include "io/serializable.h"
#include "resource/resource.h"

#include <string>

namespace Cairn::Graphics {

/** An image resource. */
class Image : public Resources::Resource, public Serializable {

public:
  Image() : width(0), height(0), num_channels(0), pixels(nullptr) {}

  ~Image();

  virtual std::string serialize() const override;

  virtual bool deserialize(const std::string& data) override;

  /** The width of the image. */
  int width;

  /** The height of the image. */
  int height;

  /** The number of channels in the image. */
  int num_channels;

  /** The pixel data of the image. */
  unsigned char* pixels;
};

} // namespace Cairn::Graphics
