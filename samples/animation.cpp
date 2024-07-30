#include "engine.h"

#include <memory>
#include <vector>

using namespace Cairn::Animation;
using namespace Cairn::ECS;
using namespace Cairn::Graphics;
using namespace Cairn::Window;

int main() {
  Window window(800, 600, "Cairn - Animation Sample");
  window.show();

  Graphics graphics(window);

  Cairn::Animation::System animation_system;
  Renderer animation_renderer(graphics);

  // Load the images to animate.
  Cairn::Resources::Manager resource_manager;
  Spritesheet* spritesheet = resource_manager.load_spritesheet("samples/assets/animation/flame_spritesheet.png");

  // Create the animation and the entity.
  Region region = spritesheet->get_region("flame0.png");
  Region region2 = spritesheet->get_region("flame1.png");
  Region region3 = spritesheet->get_region("flame2.png");
  std::vector<Frame> frames = {Frame(spritesheet, region.x, region.y, region.w, region.h),
                               Frame(spritesheet, region2.x, region2.y, region2.w, region2.h),
                               Frame(spritesheet, region3.x, region3.y, region3.w, region3.h)};
  auto animation = std::make_unique<Animation>(std::move(frames));
  animation->should_loop = true;
  animation->play();
  auto node = std::make_unique<AnimationNode>(std::move(animation));

  Entity entity;
  auto* animation_component = entity.add_component<Cairn::Animation::Component>(std::move(node));
  animation_system.add_entity(&entity);
  animation_renderer.add_entity(&entity);

  // Run the game loop.
  while (window.is_open()) {
    animation_system.update();
    animation_renderer.update();
    window.refresh();
  }
  return 0;
}