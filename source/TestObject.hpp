#pragma once
#include "scene/GameObject.hpp"
#include <eng.hpp>

class TestObject : public eng::GameObject {
public:
  TestObject();

  void Update(float deltaTime) override;

private:
  std::shared_ptr<eng::Mesh> m_mesh;
  eng::Material m_material;
};
