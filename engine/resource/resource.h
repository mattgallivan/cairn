#pragma once

#include <atomic>
#include <string>

namespace Cairn::Resources {

/**
 * A resource is an abstract class that represents a resource that can be used by the engine.
 * Resources are identified by their unique ID, which is generated automatically when the resource is created.
 */
class Resource {

public:
  /** Reset the next ID counter to 0. This is dangerous, and mainly used for testing. */
  static void reset_next_id() { next_id.store(0, std::memory_order_relaxed); }

  Resource() : id(next_id.fetch_add(1, std::memory_order_relaxed)) {}

  virtual ~Resource() = default;

  /** Get the ID of the resource. */
  int get_id() { return this->id; }

protected:
  /** The next ID to assign to a resource. */
  static std::atomic<int> next_id;

  /** The unique ID of the resource. */
  std::atomic<int> id;
};

}; // namespace Cairn::Resources
