#pragma once

#include "animation.h"
#include "component.h"
#include "node.h"

#include "ecs/entity.h"
#include "ecs/system.h"
#include "graphics/graphics.h"
#include "log/log.h"

namespace Cairn::Animation {

class Renderer : public ECS::System {

public:
  Renderer(Graphics::Graphics& graphics) : graphics(graphics) {}

  void update(float delta_time_ms = 33.33f) override;

private:
  Graphics::Graphics& graphics;
};

} // namespace Cairn::Animation