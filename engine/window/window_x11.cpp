#include <X11/Xlib.h>

#include "window_x11.h"

namespace Cairn {

Window_X11::Window_X11(U32 width, U32 height) {
  this->width = width;
  this->height = height;

  display = XOpenDisplay(nullptr);
  if (display == nullptr) {
    return;
  }

  screen = DefaultScreen(display);
  root = RootWindow(display, screen);

  window = XCreateSimpleWindow(display, root, 0, 0, width, height, 1,
                               BlackPixel(display, screen),
                               WhitePixel(display, screen));

  XSelectInput(display, window, ExposureMask | KeyPressMask);
  XMapWindow(display, window);
}

Window_X11::~Window_X11() {
  XDestroyWindow(display, window);
  XCloseDisplay(display);
}

} // namespace Cairn
