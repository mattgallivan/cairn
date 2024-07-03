#pragma once

namespace Cairn::ECS {

class Component {

public:
  virtual ~Component() = default;

  virtual void start() = 0;

  virtual void stop() = 0;

  virtual void update(float delta_time_ms) = 0;
};

} // namespace Cairn::ECS