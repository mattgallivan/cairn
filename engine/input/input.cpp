#include "input.h"

#include "log.h"

namespace Cairn {
namespace Input {

void Profile::bind(Key key, Action action, Callback callback) {
  if (should_debug) {
    Log::info(Log::Category::Input, "Bind (" + key_to_string[key] + " " + action_to_string[action] + ")");
  }

  key_callbacks[key][action].push_back(callback);
}

void Profile::fire(Key key, Action action) {
  if (should_debug) {
    Log::info(Log::Category::Input, "Fire (" + key_to_string[key] + " " + action_to_string[action] + ")");
  }

  for (auto& callback : key_callbacks[key][action]) {
    callback();
  }
}

} // namespace Input
} // namespace Cairn
