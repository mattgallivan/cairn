#include "window.h"

int main() {
  Cairn::Window window(800, 600, "Cairn Engine v0.1");
  // window.hide();
  // window.show();
  // window.maximize();
  // window.minimize();
  // window.set_cursor_visible(false);
  // window.set_fullscreen(true);
  while (window.is_open()) {
    window.refresh();
  }
  return 0;
}
