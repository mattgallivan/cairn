#pragma once

#include "input_event.h"

#include <functional>

namespace Cairn {

using InputAction = std::function<void(const InputEvent&)>;

} // namespace Cairn
