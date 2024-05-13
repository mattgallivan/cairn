#pragma once

#include "mesh.h"
#include "texture.h"

#include <glm/glm.hpp>

namespace Cairn {

/** The layer determines the order in which sprites are rendered. */
enum class SpriteLayer {
  Background,
  Foreground,
};

/** A sprite is a 2D object that can be rendered to the screen. */
class Sprite {

public:
  Sprite(Mesh* mesh, Texture* texture, SpriteLayer layer = SpriteLayer::Foreground)
      : mesh(mesh), texture(texture), layer(layer) {}

  /** Get the model matrix for this sprite. */
  glm::mat4 get_model() const;

  /** The mesh used to render this sprite. */
  Mesh* mesh;

  /** The texture used to render this sprite. */
  Texture* texture;

  /** The layer determines the order in which sprites are rendered. */
  SpriteLayer layer;

  /** The position of the sprite. */
  glm::vec2 position = glm::vec2(0.0f, 0.0f);

  /** The rotation of the sprite in degrees. */
  float rotation = 0.f;

  /** The scale of the sprite. */
  glm::vec2 scale = glm::vec2(1.0f, 1.0f);
};

} // namespace Cairn
