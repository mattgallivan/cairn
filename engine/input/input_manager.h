#pragma once

#include "input_profile.h"

#include <vector>

class InputEvent;

namespace Cairn {

/** An input manager dispatches all reported input events to the appropriate input profiles. */
class InputManager {

public:
  /** Add a new input profile to the manager. */
  void add(InputProfile* profile);

  /** Remove an input profile from the manager. */
  void remove(InputProfile* profile);

  /** Send an input event to the manager. */
  void send(const InputEvent& event);

private:
  /** The list of input profiles managed by this manager. */
  std::vector<InputProfile*> profiles;
};

} // namespace Cairn
