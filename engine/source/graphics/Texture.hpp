#pragma once

#include "graphics/ShaderProgram.hpp"
#include <memory>
namespace eng {

class Texture {

public:
  Texture(int width, int height, int numChannels, unsigned char* data);
  ~Texture();
  GLuint GetID() const;
  void Init(int width, int height, int numChannels, unsigned char* data);

  static std::shared_ptr<Texture> Load(const std::string& path);

private:
  int m_width = 0;
  int m_height = 0;
  int m_numChannels = 0;
  GLuint m_textureID = 0;
};

} // namespace eng
