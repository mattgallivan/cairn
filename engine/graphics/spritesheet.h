#pragma once

#include "graphics/image.h"
#include "io/serializable_json.h"

#include <nlohmann/json.hpp>

#include <string>
#include <unordered_map>

namespace Cairn::Graphics {

class Region {
public:
  Region() = default;

  Region(std::string filename, int x, int y, int w, int h) : filename(filename), x(x), y(y), w(w), h(h) {}

  std::string filename;

  int x, y, w, h;
};

class Spritesheet : public JSONSerializable {
public:
  Spritesheet() = default;

  Region get_region(const std::string& region_name) const;

protected:
  virtual nlohmann::json to_json() const override;

  virtual bool from_json(const nlohmann::json& json) override;

private:
  Image* image;

  std::unordered_map<std::string, Region> regions;
};

} // namespace Cairn::Graphics