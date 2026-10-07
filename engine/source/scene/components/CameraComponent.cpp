#include "CameraComponent.hpp"
#include "glm/gtc/quaternion.hpp"
#include "scene/GameObject.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace eng {

void CameraComponent::Update(float deltaTime) {}

glm::mat4 CameraComponent::GetViewMatrix() const {

  glm::mat4 mat = glm::mat4(1.0f);
  mat = glm::mat4_cast(m_owner->GetRotation());

  mat[3] = glm::vec4(m_owner->GetPosition(), 1.0f);

  if (m_owner->GetParent()) {

    mat = m_owner->GetParent()->GetWorldTransform() * mat;
  }

  return glm::inverse(mat);
}

glm::mat4 CameraComponent::GetProjectionMatrix(float aspect) const {

  return glm::perspective(glm::radians(m_fov), aspect, m_nearPlane, m_farPlane);
}

} // namespace eng
