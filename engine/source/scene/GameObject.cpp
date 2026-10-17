#include "GameObject.hpp"
#include "Engine.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "graphics/Texture.hpp"
#include "render/Mesh.hpp"
#include "scene/components/MeshComponent.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#define CGLTF_IMPLEMENTATION
#include <cgltf.h>

namespace eng {

void GameObject::Update(float deltaTime) {

  for (auto& component : m_components) {

    component->Update(deltaTime);
  }

  for (auto it = m_children.begin(); it != m_children.end();) {
    if ((*it)->isAlive()) {
      (*it)->Update(deltaTime);
      ++it;
    } else {
      it = m_children.erase(it);
    }
  }
}

const std::string& GameObject::GetName() const { return m_name; }
void GameObject::SetName(const std::string& name) { m_name = name; }
GameObject* GameObject::GetParent() { return m_parent; }

bool GameObject::SetParent(GameObject* parent) {
  if (!m_scene) {
    return false;
  }

  return m_scene->SetParent(this, parent);
}

Scene* GameObject::GetScene() { return m_scene; }

bool GameObject::isAlive() { return m_isAlive; }
void GameObject::MarkForDestroy() { m_isAlive = false; }

void GameObject::AddComponent(Component* component) {

  m_components.emplace_back(component);
  component->m_owner = this;
}

const glm::vec3& GameObject::GetPosition() const { return m_position; }

void GameObject::SetPosition(const glm::vec3& pos) { m_position = pos; }

glm::vec3 GameObject::GetWorldPosition() const {

  glm::vec4 homCoordinates =
      GetWorldTransform() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
  return glm::vec3(homCoordinates) / homCoordinates.w;
}

const glm::quat& GameObject::GetRotation() const { return m_rotation; }

void GameObject::SetRotation(const glm::quat& rot) { m_rotation = rot; }

const glm::vec3& GameObject::GetScale() const { return m_scale; }

void GameObject::SetScale(const glm::vec3& scale) { m_scale = scale; }

glm::mat4 GameObject::GetLocalTransform() const {

  glm::mat4 mat = glm::mat4(1.0f);

  // translation
  mat = glm::translate(mat, m_position);

  // rotation
  mat = mat * glm::mat4_cast(m_rotation);

  mat = glm::scale(mat, m_scale);

  return mat;
}

glm::mat4 GameObject::GetWorldTransform() const {

  if (m_parent) {

    return m_parent->GetWorldTransform() * GetLocalTransform();

  } else {

    return GetLocalTransform();
  }
}

void ParseGLTFNode(cgltf_node* node, GameObject* parent,
                   const std::filesystem::path& folder) {
  auto object = parent->GetScene()->CreateObject(
      node->name ? node->name : "Node", parent);

  if (node->has_matrix) {
    auto mat = glm::make_mat4(node->matrix);
    glm::vec3 translation, scale, skew;
    glm::vec4 perspective;
    glm::quat orientation;
    glm::decompose(mat, scale, orientation, translation, skew, perspective);

    object->SetPosition(translation);
    object->SetRotation(orientation);
    object->SetScale(scale);

  } else {
    if (node->has_translation) {
      object->SetPosition(glm::vec3(node->translation[0], node->translation[1],
                                    node->translation[2]));
    }

    if (node->has_rotation) {
      object->SetRotation(glm::quat(node->rotation[3], node->rotation[0],
                                    node->rotation[1], node->rotation[2]));
    }

    if (node->has_scale) {
      object->SetScale(
          glm::vec3(node->scale[0], node->scale[1], node->scale[2]));
    }
  }

  if (node->mesh) {
    for (cgltf_size pi = 0; pi < node->mesh->primitives_count; ++pi) {
      auto& primitives = node->mesh->primitives[pi];
      if (primitives.type != cgltf_primitive_type_triangles) {
        continue;
      }

      auto readFloats = [](const cgltf_accessor* acc, cgltf_size i, float* out,
                           int n) {
        std::fill(out, out + n, 0.0f);
        return cgltf_accessor_read_float(acc, i, out, n) != 0;
      };

      auto readIndex = [](const cgltf_accessor* acc, cgltf_size i) {
        cgltf_uint out = 0;
        cgltf_bool ok = cgltf_accessor_read_uint(acc, i, &out, 1);
        return ok ? static_cast<uint32_t>(out) : 0u;
      };

      VertexLayout vertexLayout;
      cgltf_accessor* accessors[4] = {};

      for (cgltf_size ai = 0; ai < primitives.attributes_count; ++ai) {

        auto& attr = primitives.attributes[ai];
        auto acc = attr.data;
        if (!acc) {

          continue;
        }

        VertexElement element;
        element.type = GL_FLOAT;

        switch (attr.type) {

        case cgltf_attribute_type_position: {

          accessors[VertexElement::PositionIndex] = acc;
          element.index = VertexElement::PositionIndex;
          element.size = 3;

        } break;
        case cgltf_attribute_type_color: {

          if (attr.index != 0) {
            continue;
          }
          accessors[VertexElement::ColorIndex] = acc;
          element.index = VertexElement::ColorIndex;
          element.size = 3;

        } break;
        case cgltf_attribute_type_texcoord: {

          if (attr.index != 0) {
            continue;
          }
          accessors[VertexElement::UVIndex] = acc;
          element.index = VertexElement::UVIndex;
          element.size = 2;

        } break;
        case cgltf_attribute_type_normal: {

          accessors[VertexElement::NormalIndex] = acc;
          element.index = VertexElement::NormalIndex;
          element.size = 3;

        } break;
        default:
          continue;
        }

        if (element.size > 0) {

          element.offset = vertexLayout.stride;
          vertexLayout.stride += element.size * sizeof(float);
          vertexLayout.elements.push_back(element);
        }
      }

      if (!accessors[VertexElement::PositionIndex]) {
        continue;
      }

      auto vertexCount = accessors[VertexElement::PositionIndex]->count;

      std::vector<float> vertices;
      vertices.resize(vertexLayout.stride / sizeof(float) * vertexCount);

      for (cgltf_size vi = 0; vi < vertexCount; ++vi) {

        for (auto& el : vertexLayout.elements) {

          if (!accessors[el.index]) {
            continue;
          }

          auto index = (vi * vertexLayout.stride + el.offset) / sizeof(float);
          float* outData = &vertices[index];
          readFloats(accessors[el.index], vi, outData, el.size);
        }
      }

      std::shared_ptr<Mesh> mesh;
      if (primitives.indices) {

        auto indexCount = primitives.indices->count;
        std::vector<uint32_t> indices(indexCount);

        for (cgltf_size i = 0; i < indexCount; ++i) {

          indices[i] = readIndex(primitives.indices, i);
        }
        mesh = std::make_shared<Mesh>(vertexLayout, vertices, indices);
      } else {
        mesh = std::make_shared<Mesh>(vertexLayout, vertices);
      }

      auto mat = std::make_shared<Material>();
      mat->SetShaderProgram(
          Engine::GetInstance().GetGraphicsAPI().GetDefaultShaderProgram());

      if (primitives.material) {
        auto gltfMat = primitives.material;

        if (gltfMat->has_pbr_metallic_roughness) {
          auto pbr = gltfMat->pbr_metallic_roughness;
          auto texture = pbr.base_color_texture.texture;

          if (texture && texture->image) {

            if (texture->image->uri) {
              auto path = folder / std::string(texture->image->uri);
              auto tex = Texture::Load(path.string());
              mat->SetParam("baseColorTexture", tex);
            }
          }
        } else if (gltfMat->has_pbr_specular_glossiness) {
          auto pbr = gltfMat->pbr_specular_glossiness;
          auto texture = pbr.diffuse_texture.texture;

          if (texture && texture->image) {

            if (texture->image->uri) {
              auto path = folder / std::string(texture->image->uri);
              auto tex = Texture::Load(path.string());
              mat->SetParam("baseColorTexture", tex);
            }
          }
        }
      }

      object->AddComponent(new MeshComponent(mat, mesh));
    }
  }

  for (cgltf_size ci = 0; ci < node->children_count; ++ci) {
    ParseGLTFNode(node->children[ci], object, folder);
  }
}

GameObject* GameObject::LoadGLTF(const std::string& path) {

  auto contents = Engine::GetInstance().GetFileSystem().LoadAssetFile(path);
  if (contents.empty()) {
    return nullptr;
  }

  cgltf_options options = {};
  cgltf_data* data = nullptr;

  cgltf_result res =
      cgltf_parse(&options, contents.data(), contents.size(), &data);
  if (res != cgltf_result_success) {
    return nullptr;
  }

  auto fullPath =
      Engine::GetInstance().GetFileSystem().GetAssetsFolder() / path;
  auto fullFolderPath = fullPath.remove_filename();
  auto relativeFolderPath = std::filesystem::path(path).remove_filename();

  res = cgltf_load_buffers(&options, data, fullFolderPath.string().c_str());
  if (res != cgltf_result_success) {
    cgltf_free(data);
    return nullptr;
  }

  if (data->scenes_count == 0) {
    cgltf_free(data);
    return nullptr;
  }

  auto resultObject = Engine::GetInstance().GetScene()->CreateObject("Result");
  auto scene = data->scene ? data->scene : &data->scenes[0];

  for (cgltf_size i = 0; i < scene->nodes_count; ++i) {
    auto node = scene->nodes[i];
    ParseGLTFNode(node, resultObject, relativeFolderPath);
  }

  cgltf_free(data);

  return resultObject;
}

} // namespace eng
