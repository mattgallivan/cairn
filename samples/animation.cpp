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

  // Create the images to animate.
  Cairn::Image image;
  image.width = 400;
  image.height = 300;
  image.pixels = new unsigned char[image.width * image.height * 4]; // [B, G, R, A]
  for (int i = 0; i < image.width * image.height; i++) {
    image.pixels[i] = (i % 16 == 0) ? 0xFF0000FF : 0xFF00FF00; // [B, G, R, A]
  }

  Cairn::Image image2;
  image2.width = 400;
  image2.height = 300;
  image2.pixels = new unsigned char[image2.width * image2.height * 4]; // [B, G, R, A]
  for (int i = 0; i < image2.width * image2.height; i++) {
    image2.pixels[i] = (i % 5 == 0) ? 0xFF00FF00 : 0xFF0000FF; // [B, G, R, A]
  }

  // Create the animation and the entity.
  std::vector<Frame> frames = {Frame(&image), Frame(&image2)};
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