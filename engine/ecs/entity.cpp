#include "entity.h"

namespace Cairn::ECS {

std::atomic<std::uint32_t> Entity::next_id{0};

} // namespace Cairn::ECS