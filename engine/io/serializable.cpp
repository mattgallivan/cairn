#include "serializable.h"

namespace Cairn {

/** Save the object to a file. */
bool Serializable::save(const std::string& file_path) const {
  std::ofstream file(file_path, std::ios::binary);
  if (!file.is_open()) {
    return false;
  }

  std::string data = serialize();
  file.write(data.c_str(), data.size());
  return file.good();
}

/** Load the object from a file. */
bool Serializable::load(const std::string& file_path) {
  std::ifstream file(file_path, std::ios::binary);
  if (!file.is_open()) {
    return false;
  }

  std::string data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  return deserialize(data);
}

} // namespace Cairn