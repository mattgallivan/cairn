#pragma once

#include "log.h"

#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>

namespace Cairn {
namespace Input {

enum class Action {
  Release = 0,
  Press = 1,
  Hold = 2,
};

static std::unordered_map<Action, std::string> action_to_string = {
    {Action::Press, "Press"},
    {Action::Release, "Release"},
    {Action::Hold, "Hold"},
};

enum class Key {
  Esc = 256,
  W = 87,
  A = 65,
  S = 83,
  D = 68,
};

static std::unordered_map<Key, std::string> key_to_string = {
    {Key::Esc, "Esc"}, {Key::W, "W"}, {Key::A, "A"}, {Key::S, "S"}, {Key::D, "D"},
};

using Callback = std::function<void()>;

class Profile {

public:
  void bind(Key key, Action action, Callback callback) {
    if (should_debug) {
      Log::info(Log::Category::Input, "Bind (" + key_to_string[key] + " " + action_to_string[action] + ")");
    }

    callbacks[key][action].push_back(callback);
  }

  void fire(Key key, Action action) {
    if (should_debug) {
      Log::info(Log::Category::Input, "Fire (" + key_to_string[key] + " " + action_to_string[action] + ")");
    }

    for (auto& callback : callbacks[key][action]) {
      callback();
    }
  }

  void set_debug(bool should_debug) { this->should_debug = should_debug; }

private:
  std::unordered_map<Key, std::unordered_map<Action, std::vector<Callback>>> callbacks;

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

private:
  std::vector<Profile*> profiles;
};

} // namespace Input

} // namespace Cairn
