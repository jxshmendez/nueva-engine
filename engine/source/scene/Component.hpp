#pragma once

namespace eng {

class GameObject;

class Component {

public:
  virtual ~Component() = default;
  virtual void Update(float deltaTime) = 0;

  GameObject* GetOwner();

protected:
  GameObject* m_owner = nullptr;

  friend class GameObject;
};
} // namespace eng
