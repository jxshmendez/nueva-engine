#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>

namespace eng {

class ShaderProgram {
public:
  ShaderProgram() = delete;
  ShaderProgram(const ShaderProgram&) = delete;
  ShaderProgram& operator=(const ShaderProgram&) = delete;
  explicit ShaderProgram(GLuint ShaderProgramID);
  ~ShaderProgram();

  void Bind();
  GLint GetUniformLocation(const std::string& name);
  void SetUniform(const std::string& name, float value);
  void SetUniform(const std::string& name, float v0, float v1);

private:
  std::unordered_map<std::string, GLint> m_uniformLocationCache;
  GLuint m_shaderProgramID = 0;
};

} // namespace eng
