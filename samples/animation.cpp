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
  Cairn::Image* image = resource_manager.load_image("samples/assets/animation/wolfsheet1.png");
  Cairn::Image* image2 = resource_manager.load_image("samples/assets/animation/wolfsheet2.png");

  // Create the animation and the entity.
  std::vector<Frame> frames = {Frame(image), Frame(image2)};
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