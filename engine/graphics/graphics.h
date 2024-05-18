#pragma once

#include "camera.h"
#include "shader.h"
#include "sprite.h"
#include "texture.h"
#include "tilemap.h"
#include "window.h"

#include <unordered_map>

namespace Cairn {

/** A graphics class that handles rendering. */
class Graphics {

public:
  Graphics(Window& window);

  ~Graphics();

  Graphics(const Graphics&) = delete;

  Graphics& operator=(const Graphics&) = delete;

  Graphics(Graphics&&) = delete;

  /** Build a mesh. This is necessary before drawing it. */
  bool build(Mesh& mesh);

  /** Build a texture. This is necessary before drawing it. */
  bool build(Texture& texture);

  /** Compile a shader. This is necessary before drawing with it. */
  bool compile(Shader& shader);

  void draw(Shader& shader, Camera& camera, std::vector<Sprite*>& sprites);

  void draw(Shader& shader, Camera& camera, Tilemap& tilemap);

private:
  /** The mesh cache. */
  std::unordered_map<std::string, GLuint> meshes;

  /** The shader cache. */
  std::unordered_map<std::string, GLuint> programs;

  /** The texture cache. */
  std::unordered_map<std::string, GLuint> textures;
};

} // namespace Cairn
