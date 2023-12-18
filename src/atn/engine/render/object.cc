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

#include "object.h"

namespace atn::engine::render {

RdrObj GenRdrObject(const std::span<const GLfloat> vertices,
                    const std::span<const GLuint> indices) {
  RdrObj obj;
  glGenVertexArrays(1, &obj.vao);
  glBindVertexArray(obj.vao);

  glGenBuffers(1, &obj.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(),
               GL_STATIC_DRAW);

  glGenBuffers(1, &obj.ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]),
               indices.data(), GL_STATIC_DRAW);

  obj.ebo_count = indices.size();
  return obj;
}

RdrObj GenRdrObject(const void* buffer, ptrdiff_t size,
                    const std::span<const GLuint> indices) {
  RdrObj obj;
  glGenVertexArrays(1, &obj.vao);
  glBindVertexArray(obj.vao);

  glGenBuffers(1, &obj.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);
  glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

  glGenBuffers(1, &obj.ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]),
               indices.data(), GL_STATIC_DRAW);

  obj.ebo_count = indices.size();
  return obj;
}

void DelRdrObject(const RdrObj &obj) {
  glDeleteBuffers(1, &obj.ebo);
  glDeleteBuffers(1, &obj.vbo);
  glDeleteVertexArrays(1, &obj.vao);
}

void SetAttribPointer(const std::vector<AttribPtr> &attrib_ptrs) {
  for (GLuint i{0}; i < static_cast<GLuint>(attrib_ptrs.size()); ++i) {
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(i, attrib_ptrs[i].size, GL_FLOAT, GL_FALSE,
                          attrib_ptrs[i].stride * sizeof(GLfloat),
                          reinterpret_cast<const void *>(attrib_ptrs[i].offset * sizeof(GLfloat)));
  }
}
}  // namespace atn::engine::render
