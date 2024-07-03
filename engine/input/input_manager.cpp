#include "input_manager.h"

#include <algorithm>

#include "log/log.h"

namespace Cairn {

void InputManager::add(InputProfile* profile) { profiles.push_back(profile); }

void InputManager::remove(InputProfile* profile) {
  profiles.erase(std::remove(profiles.begin(), profiles.end(), profile), profiles.end());
}

void InputManager::send(const InputEvent& event) {
  for (InputProfile* profile : profiles) {
    profile->send(event);
  }
}

} // namespace Cairn
