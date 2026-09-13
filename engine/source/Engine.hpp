#pragma once
#include "Application.hpp"
#include "graphics/GraphicsAPI.hpp"
#include "input/InputManager.hpp"
#include "render/RenderQueue.hpp"
#include <chrono>
#include <memory>

struct GLFWwindow;
namespace eng {

class Application;
class Engine {
public:
  static Engine& GetInstance();

private:
  Engine() = default;
  Engine(const Engine&) = delete;
  Engine(Engine&&) = delete;
  Engine& operator=(const Engine&) = delete;
  Engine& operator=(Engine&&) = delete;

public:
  bool Init(int width, int height);
  void Run();
  void Destroy();

  void SetApplication(Application* app);
  Application* GetApplication();
  InputManager& GetInputManager();
  GraphicsAPI& GetGraphicsAPI();
  RenderQueue& GetRenderQueue();

private:
  std::unique_ptr<Application> m_application;
  std::chrono::steady_clock::time_point m_lastTimePoint;
  GLFWwindow* m_window = nullptr;
  InputManager m_inputManager;
  GraphicsAPI m_graphicsAPI;
  RenderQueue m_renderQueue;
};
} // namespace eng
