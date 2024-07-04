#include "engine.h"

#include <memory>
#include <vector>

using namespace Cairn::Animation;
using namespace Cairn::Graphics;
using namespace Cairn::Window;

int main() {
  Window window(800, 600, "Cairn - Animation Sample");
  window.show();

  Graphics graphics(window);

  std::vector<Frame> frames;
  auto animation = std::make_unique<Animation>(std::move(frames));
  auto node = std::make_unique<AnimationNode>(std::move(animation));
  Component component(std::move(node));

  while (window.is_open()) {
    window.refresh();
  }

  return 0;
}