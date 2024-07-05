#pragma once

namespace Cairn::ECS {

/**
 * A component is an abstract piece of data that can be attached to an entity.
 *
 * (Components are used to store data. They should not contain any logic).
 */
class Component {

public:
  virtual ~Component() = default;
};

} // namespace Cairn::ECS