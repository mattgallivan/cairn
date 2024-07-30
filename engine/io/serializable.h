#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace Cairn {

/** The Serializable class is an interface for objects that can be saved to and loaded from files.
 *  The save and load methods should be implemented by the derived class.
 */
class Serializable {
public:
  virtual ~Serializable() = default;

  /** Serialize the object to a string. */
  virtual std::string serialize() const = 0;

  /** Deserialize the object from a string. */
  virtual bool deserialize(const std::string& data) = 0;

  /** Save the object to a file. */
  bool save(const std::string& file_path) const;

  /** Load the object from a file. */
  bool load(const std::string& file_path);
};

} // namespace Cairn
