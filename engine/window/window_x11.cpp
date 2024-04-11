#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "window_x11.h"

namespace Cairn {

Window_X11::Window_X11(U32 width, U32 height, const Char* title) {
  this->width = width;
  this->height = height;
  this->title = title;

  display = XOpenDisplay(nullptr);
  if (!display) {
    return;
  }

  screen = DefaultScreen(display);
  root = RootWindow(display, screen);

  window = XCreateSimpleWindow(display, root, 0, 0, width, height, 1,
                               BlackPixel(display, screen),
                               WhitePixel(display, screen));

  XStoreName(display, window, title);
  XMapWindow(display, window);
}

Window_X11::~Window_X11() {
  XDestroyWindow(display, window);
  XCloseDisplay(display);
}

void Window_X11::poll() {}

void Window_X11::set_fullscreen(Bool is_fullscreen) {
  if (is_fullscreen) {
    Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
    Atom fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

    XEvent xev;
    xev.type = ClientMessage;
    xev.xclient.window = window;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = 1;
    xev.xclient.data.l[1] = fullscreen;
    xev.xclient.data.l[2] = 0;

    XSendEvent(display, root, False,
               SubstructureRedirectMask | SubstructureNotifyMask, &xev);
  } else {
    Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
    Atom fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

    XEvent xev;
    xev.type = ClientMessage;
    xev.xclient.window = window;
    xev.xclient.message_type = wm_state;
    xev.xclient.format = 32;
    xev.xclient.data.l[0] = 0;
    xev.xclient.data.l[1] = fullscreen;
    xev.xclient.data.l[2] = 0;

    XSendEvent(display, root, False,
               SubstructureRedirectMask | SubstructureNotifyMask, &xev);
  }
}

void Window_X11::set_size(U32 width, U32 height) {
  this->width = width;
  this->height = height;
  XResizeWindow(display, window, width, height);
}

void Window_X11::set_title(const Char* title) {
  this->title = title;
  XStoreName(display, window, title);
}

void Window_X11::set_visible(Bool is_visible) {
  if (is_visible) {
    XMapWindow(display, window);
  } else {
    XUnmapWindow(display, window);
  }
}

} // namespace Cairn
