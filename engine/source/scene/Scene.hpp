#pragma once

#include <string>
#include <vector>
namespace eng {

class GameObject;

class Scene {
public:
  void Update(float deltaTime);
  void Clear();

  GameObject* CreateObject(const std::string name,
                           GameObject* parent = nullptr);

  template <typename T, typename = typename std::enable_if_t<
                            std::is_base_of_v<GameObject, T>>>
  T* CreateObject(const std::string name, GameObject* parent = nullptr);

private:
  std::vector<GameObject> m_objects;
};

} // namespace eng
