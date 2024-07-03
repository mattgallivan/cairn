#pragma once

#include "input/input.h"

#include <GL/glew.h> // This is included before GLFW to avoid a compile error.
#include <GLFW/glfw3.h>

#include <functional>
#include <set>
#include <string>
#include <vector>

namespace Cairn::Window {

/** A window for displaying graphics and polling for input. */
class Window {

public:
  Window(int width, int height, std::string title);

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
  void bind(InputManager* input_manager);

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
  std::string title;

private:
  /** Callback for when the window's framebuffer size changes (i.e., the window is resized). */
  static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

  /** Callback for when a key is pressed. */
  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

  /** Callback for when a mouse button is pressed. */
  static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

  /** Callback for when the mouse is moved. */
  static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos);

  /** A set of input managers bound to the window. */
  std::set<InputManager*> input_managers;

  /** Callbacks for when the window is resized. */
  std::vector<std::function<void(int, int)>> resize_callbacks;

  /** The underlying GLFW window. */
  GLFWwindow* window;
};

} // namespace Cairn::Window
