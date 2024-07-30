#include "animation.h"

#include "log/log.h"

namespace Cairn::Animation {

const Frame* Animation::at(int index) const {
  if (index < 0 || index >= frames.size()) {
    Log::warn(Log::Category::Animation, "Frame index out of bounds.");
    return nullptr;
  }
  return &frames[index];
}

const Frame* Animation::get_current_frame() const { return at(current_frame); }

bool Animation::is_playing() const { return is_currently_playing; }

void Animation::pause() { is_currently_playing = false; }

void Animation::play() { is_currently_playing = true; }

void Animation::reset() {
  current_frame = 0;
  time_since_last_frame_ms = 0.f;
}

void Animation::stop() {
  is_currently_playing = false;
  current_frame = 0;
  time_since_last_frame_ms = 0.f;
}

void Animation::update(float delta_time_ms) {
  if (frames.empty() || !is_currently_playing) {
    return;
  }

  time_since_last_frame_ms += delta_time_ms;

  if (time_since_last_frame_ms >= frame_duration_ms) {
    time_since_last_frame_ms = 0.f;
    current_frame = (current_frame + 1) % frames.size();

    if (current_frame == 0 && !should_loop) {
      is_currently_playing = false;
    }
  }
}

nlohmann::json Animation::to_json() const { return nlohmann::json(); }

bool Animation::from_json(const nlohmann::json& json) { return false; }

} // namespace Cairn::Animation