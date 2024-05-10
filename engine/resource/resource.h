#pragma once

#include "serializable.h"
#include "texture.h"

#include <iostream>
#include <memory>
#include <string>

namespace Cairn {

/** Base class for all resources that can be used by the engine.
 *  Resources are identified by their ID, which is unique for each resource.
 *  The ID is generated automatically when the resource is created.
 */
class Resource : public Serializable {

public:
  /** The possible states of loading a resource. */
  enum class State {
    Unloaded,
    Loading,
    Loaded,
    Failed,
  };

  Resource() : state(State::Unloaded) { this->id = std::to_string(next_id++); }

  virtual bool save(const std::string& file_path) const override { return false; }

  virtual bool load(const std::string& file_path) override { return false; }

  /** Get the ID of the resource. */
  std::string get_id() { return this->id; }

  static std::string load_shader(const std::string& file_path);

  Texture* load_texture(const std::string& file_path);

  std::vector<Texture*> textures;

protected:
  static int next_id;

  /** The unique ID of the resource. */
  std::string id;

  /** The current state of the resource. */
  State state;
};

}; // namespace Cairn
