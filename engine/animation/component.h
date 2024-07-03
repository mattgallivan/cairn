#pragma once

#include "ecs/component.h"
#include "node.h"

#include <memory>

namespace Cairn::Animation {

/** An animation component can be used by a game object to run animation logic. */
class Component : ECS::Component {

public:
  Component(std::unique_ptr<Node>&& node) : node(std::move(node)) {}

  void start() override { node->start(); }

  void stop() override { node->stop(); }

  void update(float delta_time_ms) override { node->update(delta_time_ms); }

private:
  std::unique_ptr<Node> node;
};

} // namespace Cairn::Animation