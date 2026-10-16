#include "LightComponent.hpp"

namespace eng {

void LightComponent::Update(float deltaTime) {}

const glm::vec3& LightComponent::GetColor() const { return m_color; }

void LightComponent::SetColor(const glm::vec3& color) { m_color = color; }

} // namespace eng
