#pragma once

#include "ecs/system.h"

using namespace Cairn::ECS;

namespace Cairn::Animation {

/**
 * The animation system manages all animation components and their underlying nodes.
 */
class System : public ECS::System {

public:
  void update(float delta_time_ms = 33.33f) override;
};

} // namespace Cairn::Animation