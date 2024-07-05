#pragma once

#include "animation.h"

#include <memory>

namespace Cairn::Animation {

/** A node is an abstract class that runs animation logic. */
class Node {

public:
  virtual ~Node() = default;

  /** Start the node. */
  virtual void start() = 0;

  /** Stop the node. */
  virtual void stop() = 0;

  /** Update the node with the time since the last update. */
  virtual void update(float delta_time_ms) = 0;
};

/** An animation node plays a given animation when activated. */
class AnimationNode : public Node {

public:
  AnimationNode(std::unique_ptr<Animation>&& animation) : animation(std::move(animation)) {}

  void start() override;

  void stop() override;

  void update(float delta_time_ms) override;

  Animation* get_animation() const;

private:
  /** The animation to play when this node is activated. */
  std::unique_ptr<Animation> animation;
};

} // namespace Cairn::Animation