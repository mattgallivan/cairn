#include "spritesheet.h"

using json = nlohmann::json;

namespace Cairn::Graphics {

Region Spritesheet::get_region(const std::string& region_name) const { return regions.at(region_name); }

nlohmann::json Spritesheet::to_json() const {
  json json;
  json["image"] = ""; // TODO: Implement this.
  for (const auto& [key, value] : regions) {
    json[key] = {{"x", value.x}, {"y", value.y}, {"w", value.w}, {"h", value.h}};
  }
  return json;
}

bool Spritesheet::from_json(const nlohmann::json& json) {
  std::string image_filename = json["image"];
  // image = resource_manager->load_image(image_filename);
  for (const auto& item : json.items()) {
    std::string filename = item.key();
    int x = item.value()["x"];
    int y = item.value()["y"];
    int w = item.value()["w"];
    int h = item.value()["h"];
    regions[filename] = Region(filename, x, y, w, h);
  }
  return true;
}

} // namespace Cairn::Graphics