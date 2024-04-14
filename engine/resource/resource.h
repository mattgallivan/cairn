#pragma once

#include <string>

/** Base class for all resources that can be loaded by the engine.
 *  Resources are identified by their ID, which is unique for each resource.
 *  The ID is generated automatically when the resource is created.
 */
class Resource {

public:
  Resource(std::string file_path, std::string extension) : filepath(file_path), extension(extension) {
    this->id = std::to_string(next_id++);
  }

  virtual ~Resource() {}

  /** Get the ID of the resource. */
  std::string get_id() { return this->id; }

  /** The path to the resource on disk. */
  std::string file_path;

  /** The file extension of the resource. */
  std::string file_extension;

protected:
  static int next_id;

  /** The unique ID of the resource. */
  std::string id;
};

int Resource::next_id = 0;
