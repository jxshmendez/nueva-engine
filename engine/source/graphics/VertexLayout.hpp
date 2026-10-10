#include "graphics/ShaderProgram.hpp"
#include <cstdint>
#pragma one
#include <vector>

namespace eng {

struct VertexElement {
  GLuint index; // attribute location
  GLuint size;  // num of components
  GLuint type;  // data type (e.g. GL_FLOAT)
  uint32_t offset;

  static constexpr int PositionIndex = 0;
  static constexpr int ColorIndex = 1;
  static constexpr int UVIndex = 2;
};

struct VertexLayout {
  std::vector<VertexElement> elements;
  uint32_t stride = 0; // total size of single vertex
};

} // namespace eng
