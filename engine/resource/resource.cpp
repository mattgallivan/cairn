#include "resource.h"

#include <atomic>

namespace Cairn::Resources {

std::atomic<int> Resource::next_id{0};

} // namespace Cairn::Resources
