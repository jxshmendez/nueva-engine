#pragma once

#include "glm/ext/matrix_float4x4.hpp"
namespace eng {

struct CameraData {
  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;
  glm::vec3 position;
};

struct LightData {
  glm::vec3 color;
  glm::vec3 position;
};

} // namespace eng
