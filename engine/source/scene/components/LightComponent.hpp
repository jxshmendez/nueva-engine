#pragma once

#include "glm/ext/vector_float3.hpp"
#include "scene/Component.hpp"

namespace eng {

class LightComponent : public Component {

  COMPONENT(LightComponent)
public:
  void Update(float deltaTime) override;

  const glm::vec3& GetColor() const;
  void SetColor(const glm::vec3& color);

private:
  glm::vec3 m_color = glm::vec3(1.0f);
};

} // namespace eng
