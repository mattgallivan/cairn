#pragma once

#include "ecs/component.h"
#include "node.h"

#include <memory>

namespace Cairn::Animation {

/** An animation component can be used by a game object to run animation logic. */
class Component : public ECS::Component {

public:
  Component(std::unique_ptr<Node>&& node) : node(std::move(node)) {}

  Node* get_node() const { return node.get(); }

private:
  std::unique_ptr<Node> node;
};

} // namespace Cairn::Animation