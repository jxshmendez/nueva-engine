#pragma once

#include "render/Material.hpp"
#include "scene/Component.hpp"
#include <memory>

namespace eng {

class Material;
class Mesh;

class MeshComponent : public Component {

public:
  MeshComponent(std::shared_ptr<Material>& material,
                std::shared_ptr<Mesh>& mesh);
  void Update(float deltaTime) override;

private:
  std::shared_ptr<Material> m_material;
  std::shared_ptr<Mesh> m_mesh;
};

} // namespace eng
