#pragma once

#include "frame.h"

#include "graphics/image.h"
#include "io/serializable_json.h"
#include "resource/manager.h"
#include "resource/resource.h"

#include <vector>

namespace Cairn::Animation {

/**
 * An animation is a set of frames to be played in sequence.
 *
 * The animation can be paused, played, stopped, and reset.
 * The duration of each frame can be set, and the animation can loop.
 *
 * Every animation is a resource that can also be saved and loaded.
 */
class Animation : public Resources::Resource, public JSONSerializable {

public:
  Animation() = default;

  explicit Animation(const std::vector<Frame>&& frames, bool should_loop = false)
      : frames(frames), should_loop(should_loop) {}

  /** Get the frame at the given index. */
  const Frame* at(int index) const;

  /** Get the current frame being displayed. */
  const Frame* get_current_frame() const;

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

protected:
  virtual nlohmann::json to_json() const override;

  virtual bool from_json(const nlohmann::json& json) override;
};

} // namespace Cairn::Animation