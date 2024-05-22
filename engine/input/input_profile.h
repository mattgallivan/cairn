#pragma once

#include "input_action.h"
#include "input_event.h"

#include <unordered_map>

namespace Cairn {

/** An input profile is a mapping of input events to input actions that can be added to an input manager. */
class InputProfile {

public:
  /** Map an input event to an input action. */
  void map(InputEvent event, InputAction action);

  /** Unmap an input event. */
  void unmap(InputEvent event);

  /** Send an input event to this profile. */
  void send(const InputEvent& event);

private:
  /** Map of input events to input actions. */
  std::unordered_map<InputEvent, InputAction> input_map;
};

} // namespace Cairn
