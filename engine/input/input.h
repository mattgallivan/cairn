#pragma once

#include "input_action.h"
#include "input_event.h"
#include "input_manager.h"
#include "input_profile.h"

#include "log.h"

#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace Cairn {
namespace Input {

/** An input action is a key press, release, or hold. */
enum class Action {
  Release = 0,
  Press = 1,
  Hold = 2,
};

/** A mapping from an action to a string representation. */
static std::unordered_map<Action, std::string> action_to_string = {
    {Action::Press, "Press"},
    {Action::Release, "Release"},
    {Action::Hold, "Hold"},
};

/** An input key is a key on the keyboard. */
enum class Key {
  Esc = 256,
  W = 87,
  A = 65,
  S = 83,
  D = 68,
};

/** A mapping from a key to a string representation. */
static std::unordered_map<Key, std::string> key_to_string = {
    {Key::Esc, "Esc"}, {Key::W, "W"}, {Key::A, "A"}, {Key::S, "S"}, {Key::D, "D"},
};

/** A callback is a function that is called when an input event occurs. */
using Callback = std::function<void()>;

/** A profile is a collection of bindings and their associated callbacks. */
class Profile {

public:
  void bind(Key key, Action action, Callback callback);

  void fire(Key key, Action action);

  void set_debug(bool should_debug) { this->should_debug = should_debug; }

private:
  std::unordered_map<Key, std::unordered_map<Action, std::vector<Callback>>> key_callbacks;

  bool should_debug = false;
};

class Manager {

public:
  void add(Profile* profile) {
    if (!profile) {
      Log::error(Log::Category::Input, "Profile is null");
      return;
    }

    profiles.push_back(profile);
  }

  void fire(int key, int action) {
    for (auto& profile : profiles) {
      profile->fire(static_cast<Key>(key), static_cast<Action>(action));
    }
  }

  void fire_mouse(double x_pos, double y_pos) {
    Log::info(Log::Category::Input, "Fire (" + std::to_string(x_pos) + ", " + std::to_string(y_pos) + ")");

    // TODO: Fire a porfile?
  }

private:
  std::vector<Profile*> profiles;
};

} // namespace Input

} // namespace Cairn
