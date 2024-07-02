#pragma once

#include <functional>
#include <memory>
#include <stdexcept>
#include <vector>

// #include "image.h"

struct Image {};

namespace Cairn::Animation {

/**
 * An animation frame is a single image that will be played in an animation.
 *
 * \code
 * std::shared_ptr<Image> image = std::make_shared<Image>();
 * Cairn::Animation::Frame frame(image.get());
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
 * std::shared_ptr<Image> image = std::make_shared<Image>();
 * Cairn::Animation::Frame frame(image.get());
 * std::vector<Cairn::Animation::Frame> frames = {frame};
 * Cairn::Animation::Animation animation(frames);
 * \endcode
 */
class Animation {
public:
  Animation() = default;

  explicit Animation(const std::vector<Frame>& frames) : frames(frames) {}

  /** Get the frame at the given index. */
  const Frame& at(int index) const {
    if (index < 0 || index >= frames.size()) {
      throw std::out_of_range("Index out of range.");
    }
    return frames.at(index);
  }

  /** Get the current frame being displayed. */
  const Frame& get_current_frame() const {
    if (frames.empty()) {
      throw std::out_of_range("No frames in animation.");
    }
    return at(current_frame);
  }

  bool is_playing() const { return is_currently_playing; }

  /** Pause the animation. */
  void pause() { is_currently_playing = false; }

  /** Play the animation. */
  void play() { is_currently_playing = true; }

  /** Reset the animation to the first frame. */
  void reset() { current_frame = 0; }

  /** Stop the animation. */
  void stop() {
    is_currently_playing = false;
    current_frame = 0;
    time_since_last_frame_ms = 0.f;
  }

  /** Update the animation. */
  void update(float delta_time_ms) {
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

// /**
//  * A node is an abstract class representing a state in the state machine.
//  */
// class Node {
// public:
//   virtual ~Node() = default;

//   virtual void update(float delta_time) = 0;
// };

// /**
//  * An animation node plays an animation when activated.
//  */
// class AnimationNode : public Node {
// public:
//   AnimationNode(std::unique_ptr<Animation> animation) : animation(std::move(animation)) {}

//   void update(float delta_time) override { animation->update(delta_time); }

// private:
//   /** The animation to play when this node is activated. */
//   std::unique_ptr<Animation> animation;
// };

// /**
//  * An edge connects two nodes in a state machine.
//  */
// class Edge {
// public:
//   Edge(std::weak_ptr<Node> destination, std::weak_ptr<Node> source) : destination(destination), source(source) {}

//   void set_condition(std::function<bool()> condition) { this->condition = condition; }

//   bool should_transition() { return condition(); }

//   /** The end node. */
//   std::weak_ptr<Node> destination;

//   /** The start node. */
//   std::weak_ptr<Node> source;

// private:
//   /** The condition upon which this edge should transition from source to destination. */
//   std::function<bool()> condition;
// };

// /**
//  * A state machine controls the current animation being played.
//  */
// class StateMachine {

// public:
//   void add_edge(std::weak_ptr<Node> destination, std::weak_ptr<Node> source) {
//     edges.emplace_back(destination, source);
//   }

//   void add_node(Node node) { nodes.push_back(node); }

//   void start() {}

//   void stop() {}

//   void update(float delta_time) {
//     for (auto& edge : edges) {
//       if (current_node.lock() == edge.source.lock() && edge.should_transition()) {
//         current_node = edge.destination;
//       }

//       current_node.lock()->update(delta_time);
//     }
//   }

// private:
//   /** The current node in the state machine. */
//   std::weak_ptr<Node> current_node;

//   /** The edges connecting the nodes in the state machine. */
//   std::vector<Edge> edges;

//   /** The nodes (states) of the state machine. */
//   std::vector<Node> nodes;
// };

} // namespace Cairn::Animation