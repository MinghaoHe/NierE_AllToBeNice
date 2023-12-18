/****************************************************************************
**
** Copyright (C) 2024 MinghaoHe Private.
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
#ifndef INCLUDE_ATN_GAME_POD_TRAIL_DATA
#define INCLUDE_ATN_GAME_POD_TRAIL_DATA

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace atn::game::pod_trail::data {

inline const GLfloat cube_vertices[]{
        -0.012f, -0.012f, -0.012f,
         0.012f, -0.012f, -0.012f,
         0.012f,  0.012f, -0.012f,
        -0.012f,  0.012f, -0.012f,
        -0.012f, -0.012f,  0.012f,
         0.012f, -0.012f,  0.012f,
         0.012f,  0.012f,  0.012f,
        -0.012f,  0.012f,  0.012f};

inline const GLuint cube_indices[]{
        0, 1, 3, 1 ,2 ,3,
        1, 2, 5, 2, 5, 6,
        2, 3, 6, 3, 6, 7,
        0, 1, 4, 1, 4, 5,
        0, 3, 4, 3, 4, 7,
        4, 5, 6, 4, 6, 7};

inline const GLuint prism_indices[]{
        0, 1, 0, 3,
        1, 2, 2, 3,
        4, 5, 4, 7,
        5, 6, 6, 7,
        0, 4, 1, 5,
        2, 6, 3, 7};

inline const glm::vec3 cube_color{0.65f};

inline const glm::vec3 prism_color{0.85f};

inline const size_t life{250};

inline const float speed{0.1f};

inline const float rotation_speed{0.5f};

}  // namespace atn::game::pod_trail::data

#endif  // !INCLUDE_ATN_GAME_POD_TRAIL_DATA
