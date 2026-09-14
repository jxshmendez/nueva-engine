#include "Scene.hpp"
#include "scene/GameObject.hpp"
#include <algorithm>
#include <memory>

namespace eng {

void Scene::Update(float deltaTime) {
  for (auto it = m_objects.begin(); it != m_objects.end();) {
    if ((*it)->isAlive()) {
      (*it)->Update(deltaTime);
      ++it;
    } else {
      it = m_objects.erase(it);
    }
  }
}

void Scene::Clear() { m_objects.clear(); }

GameObject* Scene::CreateObject(const std::string& name, GameObject* parent) {

  auto obj = new GameObject();
  obj->SetName(name);
  SetParent(obj, parent);
  return obj;
}

bool Scene::SetParent(GameObject* obj, GameObject* parent) {

  bool result = false;
  auto currentParent = obj->GetParent();

  if (parent == nullptr) {
    if (currentParent != nullptr) {
      auto it = std::find_if(currentParent->m_children.begin(),
                             currentParent->m_children.end(),
                             [obj](const std::unique_ptr<GameObject>& el) {
                               return el.get() == obj;
                             });

      if (it != currentParent->m_children.end()) {
        m_objects.push_back(std::move(*it));
        obj->m_parent = nullptr;
        currentParent->m_children.erase(it);
        result = true;
      }
    }
    // no parent yet. Can be 2 cases
    // 1. The object is in the scene root
    // 2. Object has just been created.
    else {
      auto it = std::find_if(m_objects.begin(), m_objects.end(),
                             [obj](const std::unique_ptr<GameObject>& el) {
                               return el.get() == obj;
                             });

      if (it == m_objects.end()) {
        std::unique_ptr<GameObject> objHolder(obj);
        m_objects.push_back(std::move(objHolder));
        result = true;
      }
    }
  }
  // move the object to a different parent
  else {
    if (currentParent != nullptr) {
      auto it = std::find_if(currentParent->m_children.begin(),
                             currentParent->m_children.end(),
                             [obj](const std::unique_ptr<GameObject>& el) {
                               return el.get() == obj;
                             });

      if (it != currentParent->m_children.end()) {
        bool found = false;
        auto currentElement = parent;
        while (currentElement) {
          if (currentElement == obj) {
            found = true;
            break;
          }
          currentElement = currentElement->GetParent();
        }

        if (!found) {
          parent->m_children.push_back(std::move(*it));
          obj->m_parent = parent;
          currentParent->m_children.erase(it);
          result = true;
        }
      }
    }
    // no parent yet. Can be 2 cases
    // 1. The object is in the scene root
    // 2. Object has just been created.

    else {
      auto it = std::find_if(m_objects.begin(), m_objects.end(),
                             [obj](const std::unique_ptr<GameObject>& el) {
                               return el.get() == obj;
                             });

      // The obj has just been created
      if (it == m_objects.end()) {
        std::unique_ptr<GameObject> objHolder(obj);
        parent->m_children.push_back(std::move(objHolder));
        obj->m_parent = parent;
        result = true;
      } else {
        bool found = false;
        auto currentElement = parent;
        while (currentElement) {
          if (currentElement == obj) {
            found = true;
            break;
          }
          currentElement = currentElement->GetParent();
        }

        if (!found) {
          parent->m_children.push_back(std::move(*it));
          obj->m_parent = parent;
          m_objects.erase(it);
          result = true;
        }
      }
    }
  }

  return result;
}

} // namespace eng
