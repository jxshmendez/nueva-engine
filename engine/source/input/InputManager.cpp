#include "InputManager.hpp"

namespace eng {

void InputManager::SetKeyPressed(int key, bool pressed) {

  if (key < 0 || key >= static_cast<int>(m_keys.size())) {
    return;
  }
  m_keys[key] = pressed;
}

bool InputManager::IsKeyPressed(int key) {

  if (key < 0 || key >= static_cast<int>(m_keys.size())) {
    return false;
  } else {
    return m_keys[key];
  }
}

} // namespace eng
