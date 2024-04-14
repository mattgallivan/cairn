#pragma once

namespace Cairn {

/** The Serializable class is an interface for objects that can be saved to and loaded from files.
 *  The save and load methods should be implemented by the derived class.
 */
class Serializable {
public:
  virtual ~Serializable() = default;

  /** Save the object to a file. */
  virtual bool save(const std::string& file_path) const = 0;

  /** Load the object from a file. */
  virtual bool load(const std::string& file_path) = 0;
};

} // namespace Cairn
