#include "GameObject.hpp"

namespace eng {

void GameObject::Update(float deltaTime) {
  for (auto it = m_children.begin(); it != m_children.end();) {
    if ((*it)->isAlive()) {
      (*it)->Update(deltaTime);
      ++it;
    } else {
      it = m_children.erase(it);
    }
  }
}

const std::string& GameObject::GetName() const { return m_name; }
void GameObject::SetName(const std::string& name) { m_name = name; }
GameObject* GameObject::GetParent() { return m_parent; }
bool GameObject::isAlive() { return m_isAlive; }
void GameObject::MarkForDestroy() { m_isAlive = false; }

} // namespace eng
