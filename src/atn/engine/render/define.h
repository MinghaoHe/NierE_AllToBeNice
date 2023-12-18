/****************************************************************************
**
** Copyright (C) 2023 MinghaoHe Private.
**
** This file is part of the NierE_AllToBeNice, which is the shoot game for ending 'E' in Nier.
**
** Licensed under the MIT license.
** A copy of the MIT License is included in this file.
**
**
** $BEGIN_LICENSE:MIT$
**
** Terms of the MIT License:
** Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
** documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
** rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in all copies or substantial portions of
** the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
** LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
** NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
** WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
** $END_LICENSE$
**
****************************************************************************/

#pragma once
#ifndef INCLUDE_ATN_ENGINE_RENDER_DEFINE
#define INCLUDE_ATN_ENGINE_RENDER_DEFINE

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace atn::engine::render {

enum class PassClass {
  kNone,
  kNormal,
  kFade,
  kText,
  kBloom,
  kParticles,
};

struct PassData {
  PassData() {}
  PassData(PassClass pclass) : pass_class(pclass) {}

  PassClass pass_class = PassClass::kNone;
  glm::mat4 model{1.0f};
  glm::vec3 color{1.0f};
  GLenum draw_mode{GL_TRIANGLES};
};

struct NormalPassData : public PassData {
  NormalPassData() : PassData(PassClass::kNormal) {}

  std::vector<GLfloat> vertices;
  std::vector<GLuint> indices;
};

struct FadePassData : public PassData {
  FadePassData() : PassData(PassClass::kFade) {}

  float fade{};
  float fade_rate{0.001};
  std::vector<GLfloat> vertices;
  std::vector<GLuint> indices;
};

struct TextPassData : public PassData {
  TextPassData() : PassData(PassClass::kText) {}
  float scale{1.0f};
  float width{};
  float height{};
  std::string text;
};

struct BloomPassData : public PassData {
  BloomPassData() : PassData(PassClass::kBloom) {}

  glm::vec3 bloom_color{1.0f};
  std::vector<GLfloat> vertices;
  std::vector<GLuint> indices;
};

#pragma pack(push, 1)
struct Particle {
  float life{0.0f};
  float size{1.0f};
  glm::vec3 velocity{0.0f};
  glm::vec3 color{1.0f};
};
#pragma pack(pop)

struct ParticlesPassData : public PassData {
  ParticlesPassData() : PassData(PassClass::kParticles) {}
  size_t duration{ 0 };
  std::vector<Particle> particles;
  std::vector<GLuint> indices;
};

}  // namespace atn::engine::render

#endif  // !INCLUDE_ATN_ENGINE_RENDER_DEFINE
