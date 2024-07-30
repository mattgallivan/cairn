#include "serializable_json.h"

namespace Cairn {

bool JSONSerializable::deserialize(const std::string& data) {
  try {
    nlohmann::json json = nlohmann::json::parse(data);
    return from_json(json);
  } catch (const nlohmann::json::parse_error& e) {
    return false;
  }
}

std::string JSONSerializable::serialize() const { return to_json().dump(); }

} // namespace Cairn