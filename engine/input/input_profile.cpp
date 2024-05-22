#include "input_profile.h"

namespace Cairn {

void InputProfile::map(InputEvent event, InputAction action) { input_map[event] = action; }

void InputProfile::unmap(InputEvent event) { input_map.erase(event); }

void InputProfile::send(const InputEvent& event) {
  auto it = input_map.find(event);
  if (it != input_map.end()) {
    it->second(event);
  }
}

} // namespace Cairn
