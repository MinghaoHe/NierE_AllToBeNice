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
#ifndef INCLUDE_ATN_GAME_ENEMY_HIT_DATA
#define INCLUDE_ATN_GAME_ENEMY_HIT_DATA

#include <glad/glad.h>

namespace atn::game::enemy_hit::data {

inline const glm::vec3 color{1.0f};

inline const GLfloat vertices1[]{ 0.09f, -0.05f, 0.0f,
                                  0.05f, -0.05f, 0.0f,
                                  0.09f,  0.05f, 0.0f,
                                  0.05f,  0.05f, 0.0f,

                                 -0.05f, -0.05f, 0.0f,
                                 -0.09f, -0.05f, 0.0f,
                                 -0.05f,  0.05f, 0.0f,
                                 -0.09f,  0.05f, 0.0f,

                                  0.05f,  0.05f, 0.0f,
                                 -0.05f,  0.05f, 0.0f,
                                  0.05f,  0.09f, 0.0f,
                                 -0.05f,  0.09f, 0.0f,

                                  0.05f, -0.05f, 0.0f,
                                 -0.05f, -0.05f, 0.0f,
                                  0.05f, -0.09f, 0.0f,
                                 -0.05f, -0.09f, 0.0f};
inline const GLuint indices1[]{ 0,  1,  2,  1,  2,  3,
                                4,  5,  6,  5,  6,  7,
                                8,  9, 10,  9, 10, 11,
                               12, 13, 14, 13, 14, 15};
inline const GLfloat vertices2[]{-0.05f,  0.05f, 0.0f,
                                 -0.09f,  0.05f, 0.0f,
                                 -0.05f,  0.09f, 0.0f,
                                 -0.09f,  0.09f, 0.0f,

                                  0.09f,  0.05f, 0.0f,
                                  0.05f,  0.05f, 0.0f,
                                  0.09f,  0.09f, 0.0f,
                                  0.05f,  0.09f, 0.0f,

                                 -0.05f, -0.09f, 0.0f,
                                 -0.09f, -0.09f, 0.0f,
                                 -0.05f, -0.05f, 0.0f,
                                 -0.09f, -0.05f, 0.0f,

                                  0.09f, -0.09f, 0.0f,
                                  0.05f, -0.09f, 0.0f,
                                  0.09f, -0.05f, 0.0f,
                                  0.05f, -0.05f, 0.0f};
inline const GLuint indices2[]{ 0,  1,  2,  1,  2,  3,
                                4,  5,  6,  5,  6,  7,
                                8,  9, 10,  9, 10, 11,
                                12, 13, 14, 13, 14, 15};

inline const GLfloat vertices3[]{-0.01f,  0.06f, 0.0f,
                                 -0.09f,  0.06f, 0.0f,
                                 -0.01f,  0.09f, 0.0f,
                                 -0.09f,  0.09f, 0.0f,

                                 -0.01f,  0.01f, 0.0f,
                                 -0.09f,  0.01f, 0.0f,
                                 -0.01f,  0.04f, 0.0f,
                                 -0.09f,  0.04f, 0.0f,

                                 -0.01f, -0.01f, 0.0f,
                                 -0.09f, -0.01f, 0.0f,
                                 -0.01f, -0.04f, 0.0f,
                                 -0.09f, -0.04f, 0.0f,

                                 -0.01f, -0.06f, 0.0f,
                                 -0.09f, -0.06f, 0.0f,
                                 -0.01f, -0.09f, 0.0f,
                                 -0.09f, -0.09f, 0.0f,

                                  0.09f,  0.06f, 0.0f,
                                  0.01f,  0.06f, 0.0f,
                                  0.09f,  0.09f, 0.0f,
                                  0.01f,  0.09f, 0.0f,

                                  0.09f,  0.01f, 0.0f,
                                  0.01f,  0.01f, 0.0f,
                                  0.09f,  0.04f, 0.0f,
                                  0.01f,  0.04f, 0.0f,

                                  0.09f, -0.01f, 0.0f,
                                  0.01f, -0.01f, 0.0f,
                                  0.09f, -0.04f, 0.0f,
                                  0.01f, -0.04f, 0.0f,

                                  0.09f, -0.06f, 0.0f,
                                  0.01f, -0.06f, 0.0f,
                                  0.09f, -0.09f, 0.0f,
                                  0.01f, -0.09f, 0.0f,};
inline const GLuint indices3[]{ 0,  1,  2,  1,  2,  3,
                                4,  5,  6,  5,  6,  7,
                                8,  9, 10,  9, 10, 11,
                                12, 13, 14, 13, 14, 15,
                                16, 17, 18, 17, 18, 19,
                                20, 21, 22, 21, 22, 23,
                                24, 25, 26, 25, 26, 27,
                                28, 29, 30, 29, 30, 31,};

inline const float fade_rate = 0.0015f;

inline const size_t life{300};

}  // atn::game::pod::data

#endif  // !INCLUDE_ATN_GAME_ENEMY_HIT_DATA