#pragma once
#include "scene/GameObject.hpp"
#include <eng.hpp>

class TestObject : public eng::GameObject {
public:
  TestObject();

  void Update(float deltaTime) override;

private:
};
