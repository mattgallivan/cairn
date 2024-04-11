#include "window.h"

int main() {
  Cairn::Window window(800, 600, "My First Window");
  window.set_fullscreen(true);
  while (true) {
    window.poll();
  }
  return 0;
}
