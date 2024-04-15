#pragma once

#include "serializable.h"

#include <filesystem>
#include <iostream>
#include <string>

namespace Cairn {

/** Base class for all resources that can be used by the engine.
 *  Resources are identified by their ID, which is unique for each resource.
 *  The ID is generated automatically when the resource is created.
 */
class Resource : public Serializable {

public:
  /** The possible states of a resource. */
  enum class State {
    Unloaded,
    Loading,
    Loaded,
    Failed,
  };

  Resource(std::string file_path) : file_path(file_path), state(State::Unloaded) {
    this->id = std::to_string(next_id++);
    this->extension = std::filesystem::path(file_path).extension().string();
  }

  virtual ~Resource() {}

  virtual bool save(const std::string& file_path) const = 0;

  virtual bool load(const std::string& file_path) = 0;

  /** Get the ID of the resource. */
  std::string get_id() { return this->id; }

  /** The path to the resource on disk. */
  std::string file_path;

protected:
  static int next_id;

  /** The extension of the file. */
  std::string extension;

  /** The unique ID of the resource. */
  std::string id;

  /** The current state of the resource. */
  State state;
};

int Resource::next_id = 0;

}; // namespace Cairn
