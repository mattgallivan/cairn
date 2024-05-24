#pragma once

#include "input_event.h"

#include <functional>

namespace Cairn {

/** An input action is a callback that is called when an input event is received. */
using InputAction = std::function<void(const InputEvent&)>;

} // namespace Cairn
