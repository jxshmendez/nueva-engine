#include "render/RenderQueue.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "graphics/GraphicsAPI.hpp"

namespace eng {

void RenderQueue::Submit(const RenderCommand& command) {
  m_commands.push_back(command);
}

void RenderQueue::Draw(GraphicsAPI& graphicsAPI) {

  for (auto& command : m_commands) {
    graphicsAPI.BindMaterial(command.material);
    graphicsAPI.BindMesh(command.mesh);
    graphicsAPI.DrawMesh(command.mesh);
  }

  m_commands.clear();
}
} // namespace eng
