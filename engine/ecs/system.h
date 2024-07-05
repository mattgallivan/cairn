#pragma once

namespace Cairn::ECS {

class System {

public:
  virtual void update(Component& component, float delta_time_ms) = 0;
};

} // namespace Cairn::ECS