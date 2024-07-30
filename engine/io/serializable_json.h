#pragma once

#include "serializable.h"

#include "nlohmann/json.hpp"

#include <string>

namespace Cairn::Resources {
class Manager;
};

namespace Cairn {

class JSONSerializable : public Serializable {

public:
  virtual ~JSONSerializable() = default;

  bool deserialize(const std::string& data) override;

  std::string serialize() const override;

protected:
  virtual nlohmann::json to_json() const = 0;

  virtual bool from_json(const nlohmann::json& json) = 0;
};

} // namespace Cairn