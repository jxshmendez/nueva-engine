#include "CameraComponent.hpp"
#include "scene/GameObject.hpp"

namespace eng {

void CameraComponent::Update(float deltaTime) {}

glm::mat4 CameraComponent::GetViewMatrix() const {

  return glm::inverse(m_owner->GetWorldTransform());
}

glm::mat4 CameraComponent::GetProjectionMatrix() const {

  return glm::mat4(1.0f);
}

} // namespace eng
