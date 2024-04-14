#pragma once

#include "serializable.h"

#include <string>

/** Base class for all resources that can be used by the engine.
 *  Resources are identified by their ID, which is unique for each resource.
 *  The ID is generated automatically when the resource is created.
 */
class Resource : public Serializable {

public:
  /** The possible states of a resource. */
  enum class State { UNLOADED, LOADING, LOADED, FAILED };

  Resource(std::string file_path, std::string extension)
      : filepath(file_path), extension(extension), state(State::UNLOADED) {
    this->id = std::to_string(next_id++);
  }

  virtual ~Resource() {}

  virtual bool save(const std::string& file_path) const override = 0;

  virtual bool load(const std::string& file_path) override = 0;

  /** Get the ID of the resource. */
  std::string get_id() { return this->id; }

  /** The path to the resource on disk. */
  std::string file_path;

  /** The file extension of the resource. */
  std::string file_extension;

protected:
  static int next_id;

  /** The current state of the resource. */
  State state;

  /** The unique ID of the resource. */
  std::string id;
};

int Resource::next_id = 0;
