#pragma once

#include "graphics/image.h"

namespace Cairn::Animation {

/**
 * An animation frame is a single image that will be played in an animation.
 *
 * The frame can represent the entire image (full width and height) or a subset of the image specified by the x, y,
 * width, and height.
 */
class Frame {

public:
  Frame() = default;

  explicit Frame(Graphics::Image* image) : image(image), x(0), y(0), width(image->width), height(image->height) {}

  Frame(Graphics::Image* image, int x, int y, int width, int height)
      : image(image), x(x), y(y), width(width), height(height) {}

  bool operator==(const Frame& other) const { return image == other.image; }

  /** The image this frame will display. */
  Graphics::Image* image;

  /** The x-coordinate of the frame in the image. */
  int x = 0;

  /** The y-coordinate of the frame in the image. */
  int y = 0;

  /** The width of the frame in the image. */
  int width = 0;

  /** The height of the frame in the image. */
  int height = 0;
};

} // namespace Cairn::Animation