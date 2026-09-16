#include "MeshComponent.hpp"
#include "Engine.hpp"
#include "render/Material.hpp"
#include "render/Mesh.hpp"
#include "render/RenderQueue.hpp"
#include "scene/GameObject.hpp"

namespace eng {

MeshComponent::MeshComponent(std::shared_ptr<Material>& material,
                             std::shared_ptr<Mesh>& mesh)
    : m_material(material), m_mesh(mesh) {}

void MeshComponent::Update(float deltaTime) {

  if (!m_material || !m_mesh) {
    return;
  }

  eng::RenderCommand command;
  command.material = m_material.get();
  command.mesh = m_mesh.get();
  command.modelMatrix = GetOwner()->GetWorldTransform();

  auto& renderQueue = Engine::GetInstance().GetRenderQueue();
  renderQueue.Submit(command);
}

} // namespace eng
