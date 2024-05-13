#include "sprite.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Cairn {

glm::mat4 Sprite::get_model() const {
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));
  model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(scale, 1.0f));

  return model;
}

} // namespace Cairn
