#include "PlayerControllerComponent.hpp"
#include "Engine.hpp"
#include "input/InputManager.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace eng {

void PlayerControllerComponent::Update(float deltaTime) {

  auto& inputManager = Engine::GetInstance().GetInputManager();
  auto rotation = m_owner->GetRotation();

  if (inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {

    auto& oldPos = inputManager.GetMousePositionOld();
    auto& currentPos = inputManager.GetMousePositionCurrent();

    float deltaX = currentPos.x - oldPos.x;
    float deltaY = currentPos.y - oldPos.y;

    rotation.y -= deltaX * m_sensitivity * deltaTime;

    rotation.x -= deltaY * m_sensitivity * deltaTime;

    m_owner->SetRotation(rotation);
  }

  glm::mat4 rotMat(1.0f);
  rotMat =
      glm::rotate(rotMat, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis
  rotMat =
      glm::rotate(rotMat, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis
  rotMat =
      glm::rotate(rotMat, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis

  glm::vec3 front =
      glm::normalize(glm::vec3(rotMat * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f)));
  glm::vec3 right =
      glm::normalize(glm::vec3(rotMat * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));

  auto position = m_owner->GetPosition();

  auto& input = eng::Engine::GetInstance().GetInputManager();

  // left and right movement
  if (inputManager.IsKeyPressed(GLFW_KEY_A)) {

    position -= right * m_moveSpeed * deltaTime;

  } else if (input.IsKeyPressed(GLFW_KEY_D)) {

    position += right * m_moveSpeed * deltaTime;
  }

  // vertical movement
  if (inputManager.IsKeyPressed(GLFW_KEY_W)) {

    position += front * m_moveSpeed * deltaTime;

  } else if (inputManager.IsKeyPressed(GLFW_KEY_S)) {

    position -= front * m_moveSpeed * deltaTime;
  }
  m_owner->SetPosition(position);
}

} // namespace eng
