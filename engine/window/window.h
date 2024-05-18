#pragma once

#include "input.h"

#include <GL/glew.h> // This is included before GLFW to avoid a compile error.
#include <GLFW/glfw3.h>

#include <functional>
#include <set>
#include <vector>

namespace Cairn {

/** A window for displaying graphics and polling for input. */
class Window {

public:
  Window(int width, int height, const char* title);

  ~Window();

  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(Window&&) = delete;

  /** Get the GLFW window. */
  GLFWwindow* get_glfw_window() const;

  /** Returns true if the window is open, false otherwise. */
  bool is_open() const;

  /** Add a callback for when the window is resized. */
  void add_resize_callback(std::function<void(int, int)> callback);

  /** Bind an input manager to the window. */
  void bind(Input::Manager* input_manager);

  /** Close the window. */
  void close();

  /** Hide the window. */
  void hide();

  /** Maximize the window. */
  void maximize();

  /** Minimize the window. */
  void minimize();

  /** Refresh the window and poll for events. */
  void refresh();

  /** Set the window's cursor to be visible or not. */
  void set_cursor_visible(bool is_visible);

  /** Set the window to be fullscreen or not. */
  void set_fullscreen(bool is_fullscreen);

  /** Show the window. */
  void show();

  /** The window's height. */
  int height;

  /** If the window's cursor is visible. */
  bool is_cursor_visible = false;

  /** If the window is fullscreen. */
  bool is_fullscreen = false;

  /** The window's width. */
  int width;

  /** The window's title. */
  const char* title;

private:
  /** Callback for when the window's framebuffer size changes (i.e., the window is resized). */
  static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

  /** Callback for when a key is pressed. */
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  /** A set of input managers bound to the window. */
  std::set<Input::Manager*> input_managers;

  /** Callbacks for when the window is resized. */
  std::vector<std::function<void(int, int)>> resize_callbacks;

  /** The underlying GLFW window. */
  GLFWwindow* window;
};

} // namespace Cairn
