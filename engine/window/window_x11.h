#ifndef WINDOW_X11_H
#define WINDOW_X11_H

#include <X11/Xlib.h>

#include <../memory/types.h>

namespace Cairn {

class Window_X11 {

public:
  Window_X11(U32 width, U32 height);
  ~Window_X11();

  U32 width;
  U32 height;

private:
  Display* display;
  int screen;
  Window root;
  Window window;
};

} // namespace Cairn

#endif // WINDOW_X11_H
