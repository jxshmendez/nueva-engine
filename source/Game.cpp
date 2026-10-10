#include "Game.hpp"
#include "TestObject.hpp"
#include "graphics/Texture.hpp"
#include "io/FileSystem.hpp"
#include "scene/components/CameraComponent.hpp"
#include <GLFW/glfw3.h>

#include <memory>
#include <stb_image.h>

bool Game::Init() {

  auto fs = eng::FileSystem();
  auto texture = eng::Texture::Load("brick.png");

  m_scene = new eng::Scene();
  auto camera = m_scene->CreateObject("Camera");
  camera->AddComponent(new eng::CameraComponent());
  camera->SetPosition(glm::vec3(0.0f, 0.0f, 2.0f));
  camera->AddComponent(new eng::PlayerControllerComponent());

  m_scene->SetMainCamera(camera);

  m_scene->CreateObject<TestObject>("TestObject");

  auto material = eng::Material::Load("materials/brick.mat");

  std::vector<float> vertices = {
      // Front face
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f,
      1.0f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

      // Top face
      0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f,
      1.0f, 0.0f, 0.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

      // Right face
      0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, 0.5f, 0.0f,
      1.0f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

      // Left face
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f,
      1.0f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

      // Bottom face
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f,
      1.0f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

      // Back face
      -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, 0.5f, -0.5f, 0.0f,
      1.0f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f};

  std::vector<unsigned int> indices = {// front face
                                       0, 1, 2, 0, 2, 3,
                                       // top face
                                       4, 5, 6, 4, 6, 7,
                                       // right face
                                       8, 9, 10, 8, 10, 11,
                                       // left face
                                       12, 13, 14, 12, 14, 15,
                                       // bottom face
                                       16, 17, 18, 16, 18, 19,
                                       // back face
                                       20, 21, 22, 20, 22, 23};

  eng::VertexLayout vertexLayout;

  // position
  vertexLayout.elements.push_back({
      0,
      3,
      GL_FLOAT,
      0,
  });
  // colour
  vertexLayout.elements.push_back({1, 3, GL_FLOAT, sizeof(float) * 3});

  // uv
  vertexLayout.elements.push_back({2, 2, GL_FLOAT, sizeof(float) * 6});
  vertexLayout.stride = sizeof(float) * 8;

  auto mesh = std::make_shared<eng::Mesh>(vertexLayout, vertices, indices);

  auto objectA = m_scene->CreateObject("objectA");
  objectA->AddComponent(new eng::MeshComponent(material, mesh));
  objectA->SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));

  auto objectB = m_scene->CreateObject("objectA");
  objectB->AddComponent(new eng::MeshComponent(material, mesh));
  objectB->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
  objectB->SetRotation(glm::vec3(0.0f, 2.0f, 0.0f));

  auto objectC = m_scene->CreateObject("objectA");
  objectC->AddComponent(new eng::MeshComponent(material, mesh));
  objectC->SetPosition(glm::vec3(2.0f, 2.0f, 2.0f));
  objectC->SetRotation(glm::vec3(0.0f, 2.0f, 2.0f));
  objectC->SetScale(glm::vec3(1.5f, 1.5f, 1.5f));

  eng::Engine::GetInstance().SetScene(m_scene);
  return true;
}

void Game::Update(float deltaTime) { m_scene->Update(deltaTime); }

void Game::Destroy() {}
