#pragma once

#include <memory>
#include <string>
#include <vector>
namespace eng {

class GameObject {

public:
  virtual ~GameObject() = default;
  virtual void Update(float deltaTime);
  const std::string& GetName() const;
  void SetName(const std::string& name);
  GameObject* GetParent();
  bool isAlive();
  void MarkForDestroy();

protected:
  GameObject() = default;

private:
  std::string m_name;
  GameObject* m_parent = nullptr;
  std::vector<std::unique_ptr<GameObject>> m_children;
  bool m_isAlive = true;
};

} // namespace eng
