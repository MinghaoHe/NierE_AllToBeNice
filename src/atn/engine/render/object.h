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
#ifndef INCLUDE_ATN_ENGINE_RENDER_OBJECT
#define INCLUDE_ATN_ENGINE_RENDER_OBJECT

#include <span>
#include <vector>

#include <glad/glad.h>

namespace atn::engine::render {

struct RdrObj {
  GLuint vao{};
  GLuint vbo{};
  GLuint ebo{};
  GLsizei ebo_count{};
};

struct AttribPtr {
  GLint size{};
  GLsizei stride{};
  GLsizei offset{};
};

RdrObj GenRdrObject(const std::span<const GLfloat> vertices,
                    const std::span<const GLuint> indices);

RdrObj GenRdrObject(const void* buffer, ptrdiff_t size,
                    const std::span<const GLuint> indices);

void DelRdrObject(const RdrObj &obj);

void SetAttribPointer(const std::vector<AttribPtr> &attrib_ptrs);

}  // namespace atn::engine::render

#endif  // !INCLUDE_ATN_ENGINE_RENDER_OBJECT
