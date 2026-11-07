#pragma once
#include "glm/ext/quaternion_float.hpp"
#include "glm/ext/vector_float3.hpp"
#include "scene/Component.hpp"
#include "scene/GameObject.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace eng {

struct KeyFrameVec3 {
  float time = 0.0f;
  glm::vec3 value = glm::vec3(0.0f);
};

struct KeyFrameQuat {
  float time = 0.0f;
  glm::quat value = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
};

// holds the animation for each node, i.e left-leg animation
struct TransformTrack {
  std::string targetName;
  std::vector<KeyFrameVec3> positions;
  std::vector<KeyFrameQuat> rotations;
  std::vector<KeyFrameVec3> scales;
};

// the named animation, i.e 'walk'
struct AnimationClip {
  std::string name;
  float duration = 0.0f;
  bool looping = true;
  std::vector<TransformTrack> tracks;
};

struct ObjectBinding {
  GameObject* object = nullptr;
  std::vector<size_t> trackIndices;
};

class AnimationComponent : public Component {

  COMPONENT(AnimationComponent)

public:
  void Update(float deltaTime) override;
  void SetClip(AnimationClip* clip);
  void RegisterClip(const std::string& name,
                    const std::shared_ptr<AnimationClip>& clip);
  void Play(const std::string& name, bool loop = true);

private:
  void BuildBindings();
  glm::vec3 Interpolate(const std::vector<KeyFrameVec3>& keys, float time);
  glm::quat Interpolate(const std::vector<KeyFrameQuat>& keys, float time);

private:
  AnimationClip* m_clip = nullptr;
  float m_time = 0.0f;
  bool m_looping = true;
  bool m_isPlaying = false;

  std::unordered_map<std::string, std::shared_ptr<AnimationClip>> m_clips;
  std::unordered_map<GameObject*, std::unique_ptr<ObjectBinding>> m_bindings;
};

} // namespace eng
