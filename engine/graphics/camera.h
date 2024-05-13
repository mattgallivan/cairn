#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Cairn {

/**
 * An orthographic camera used for rendering.
 *
 * The coordinate system is as follows:
 * - The origin is at the bottom-left corner.
 * - The x-axis increases to the right.
 * - The y-axis increases upwards.
 */
class Camera {

public:
  /** Get the projection matrix. */
  glm::mat4 get_projection() const { return glm::ortho(left, right, bottom, top, near, far); }

  /** The left plane of the camera. */
  float left = 0.0f;

  /** The right plane of the camera. */
  float right = 800.0f;

  /** The bottom plane of the camera. */
  float bottom = 0.0f;

  /** The top plane of the camera. */
  float top = 600.0f;

  /** The near plane of the camera. */
  float near = -1.0f;

  /** The far plane of the camera. */
  float far = 1.0f;
};

} // namespace Cairn
