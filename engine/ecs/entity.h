#pragma once

#include "component.h"

#include <atomic>
#include <cstdint>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace Cairn::ECS {

/**
 * An entity is an abstract class that can be used to represent any object in the game world.
 * Entities are used to store components that define the behavior of the object.
 */
class Entity {

public:
  Entity() : id(next_id++) {}

  /** Get the unique identifier of the entity. */
  std::uint32_t get_id() const { return id; }

  /** Add a component to the entity. */
  template <typename T, typename... Args>
  T* add_component(Args&&... args) {
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    T* component_ptr = component.get();
    components[typeid(T)] = std::move(component);
    return component_ptr;
  }

  /** Get a component from the entity. */
  template <typename T>
  T* get_component() {
    auto it = components.find(typeid(T));
    if (it != components.end()) {
      return static_cast<T*>(it->second.get());
    }
    return nullptr;
  }

  /** Remove a component from the entity. */
  template <typename T>
  void remove_component() {
    components.erase(typeid(T));
  }

private:
  /** The next unique identifier to assign to the next entity. */
  static std::atomic<std::uint32_t> next_id;

  /** The components that define the behavior of the entity. */
  std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

  /** The unique identifier of the entity. */
  std::uint32_t id;
};

} // namespace Cairn::ECS