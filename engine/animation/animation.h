#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>

struct Image {};

namespace Cairn::Animation {

/**
 * An animation frame is a single image that will be played in an animation.
 *
 * \code
 * Image image;
 * Cairn::Animation::Frame frame(&image);
 * \endcode
 */
struct Frame {

  Frame() = default;

  explicit Frame(Image* image) : image(image) {}

  /** The image this frame will display. */
  Image* image;

  bool operator==(const Frame& other) const { return image == other.image; }
};

/**
 * An animation is a set of frames to be played in sequence.
 *
 * \code
 * Image image;
 * Cairn::Animation::Frame frame(&image);
 * std::vector<Cairn::Animation::Frame> frames = {frame};
 * Cairn::Animation::Animation animation(frames);
 * \endcode
 */
class Animation {
public:
  Animation() = default;

  explicit Animation(const std::vector<Frame>& frames) : frames(frames) {}

  /** Get the frame at the given index. */
  const Frame& at(int index) const;

  /** Get the current frame being displayed. */
  const Frame& get_current_frame() const;

  /** Returns true if the animation is currently playing. */
  bool is_playing() const;

  /** Pause the animation. */
  void pause();

  /** Play the animation. */
  void play();

  /** Reset the animation to the first frame. */
  void reset();

  /** Stop the animation. */
  void stop();

  /** Update the animation. */
  void update(float delta_time_ms);

  /** The duration of each frame. Defaults to 24 FPS. */
  float frame_duration_ms = 1000.f / 24.f;

  /** The frames in the animation clip. */
  std::vector<Frame> frames;

  /** True if the clip should loop upon ending. */
  bool should_loop = false;

private:
  /** The current frame being displayed. */
  size_t current_frame = 0;

  /** True if the animation is currently playing. */
  bool is_currently_playing = false;

  /** The time since the last frame was displayed. */
  float time_since_last_frame_ms = 0.f;
};

} // namespace Cairn::Animation