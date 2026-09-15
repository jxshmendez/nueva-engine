#include "render/RenderQueue.hpp"
#include "Material.hpp"
#include "Mesh.hpp"
#include "graphics/GraphicsAPI.hpp"
#include "graphics/ShaderProgram.hpp"

namespace eng {

void RenderQueue::Submit(const RenderCommand& command) {
  m_commands.push_back(command);
}

void RenderQueue::Draw(GraphicsAPI& graphicsAPI) {

  for (auto& command : m_commands) {
    graphicsAPI.BindMaterial(command.material);
    command.material->GetShaderProgram()->SetUniform("uModel",
                                                     command.modelMatrix);
    graphicsAPI.BindMesh(command.mesh);
    graphicsAPI.DrawMesh(command.mesh);
  }

  m_commands.clear();
}
} // namespace eng
