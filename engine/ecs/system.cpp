#include "system.h"

#include <algorithm>

namespace Cairn::ECS {

std::size_t System::num_entities() const { return entities.size(); }

void System::add_entity(Entity* entity) { entities.push_back(entity); }

void System::remove_entity(Entity* entity) {
  entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

} // namespace Cairn::ECS