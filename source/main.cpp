#include "Game.hpp"
#include <eng.hpp>

int main() {

  Game* game = new Game();
  eng::Engine& engine = eng::Engine::GetInstance();
  engine.SetApplication(game);

  if (engine.Init(1280, 720)) {
    engine.Run();
  }

  engine.Destroy();
  return 0;
}
