#pragma once

#include <vector>

namespace Cairn::ECS {

class Entity;

/**
 * A system is an abstract class that manages the updating of entities' components.
 */
class System {

public:
  virtual ~System() = default;

  /** Get the number of entities in the system. */
  std::size_t num_entities() const;

  /** Update the system after a specified amount of time has passed. */
  virtual void update(float delta_time_ms = 33.33f) = 0;

  /** Add an entity to the system. */
  void add_entity(Entity* entity);

  /** Remove an entity from the system. */
  void remove_entity(Entity* entity);

protected:
  std::vector<Entity*> entities;
};

} // namespace Cairn::ECS