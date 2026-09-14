#pragma once

#include <eng.hpp>
#include <memory.h>

class Game : public eng::Application {

public:
  bool Init() override;
  void Update(float deltaTime) override;
  void Destroy() override;

private:
  eng::Scene m_scene;
};
