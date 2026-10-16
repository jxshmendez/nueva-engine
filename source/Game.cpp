#include "Game.hpp"
#include "TestObject.hpp"
#include "graphics/Texture.hpp"
#include "io/FileSystem.hpp"
#include "render/Material.hpp"
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

  auto mesh = eng::Mesh::CreateCube();

  auto objectA = m_scene->CreateObject("objectA");
  objectA->AddComponent(new eng::MeshComponent(material, mesh));
  objectA->SetPosition(glm::vec3(1.0f, 0.0f, -8.0f));

  auto objectB = m_scene->CreateObject("objectA");
  objectB->AddComponent(new eng::MeshComponent(material, mesh));
  objectB->SetPosition(glm::vec3(0.0f, 2.0f, 2.0f));
  objectB->SetRotation(glm::vec3(0.0f, 2.0f, 0.0f));

  auto objectC = m_scene->CreateObject("objectA");
  objectC->AddComponent(new eng::MeshComponent(material, mesh));
  objectC->SetPosition(glm::vec3(2.0f, 2.0f, 2.0f));
  objectC->SetRotation(glm::vec3(0.0f, 2.0f, 2.0f));
  objectC->SetScale(glm::vec3(1.5f, 1.5f, 1.5f));

  auto suzanneMesh = eng::Mesh::Load("models/Suzanne.gltf");
  auto suzanneMaterial = eng::Material::Load("materials/suzanne.mat");

  auto suzanneObj = m_scene->CreateObject("Suzanne");
  suzanneObj->AddComponent(
      new eng::MeshComponent(suzanneMaterial, suzanneMesh));
  suzanneObj->SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));

  auto light = m_scene->CreateObject("Light");
  auto lightComp = new eng::LightComponent();
  lightComp->SetColor(glm::vec3(1.0f));
  light->AddComponent(lightComp);
  light->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));

  eng::Engine::GetInstance().SetScene(m_scene);
  return true;
}

void Game::Update(float deltaTime) { m_scene->Update(deltaTime); }

void Game::Destroy() {}
