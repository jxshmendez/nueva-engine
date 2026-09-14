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
  float m_offsetX = 0.0f;
  float m_offsetY = 0.0f;
};
