#include "engine.h"

#include <vector>

using namespace Cairn::Animation;
using namespace Cairn::Window;

int main() {
  Window window(800, 600, "Cairn - Animation Sample");
  window.show();

  std::vector<Frame> frames;
  std::unique_ptr<Animation> animation(std::make_unique<Animation>(frames));
  std::unique_ptr<Node> node = std::make_unique<AnimationNode>(std::move(animation));
  Component component(std::move(node));

  while (window.is_open()) {
    window.refresh();
  }

  return 0;
}