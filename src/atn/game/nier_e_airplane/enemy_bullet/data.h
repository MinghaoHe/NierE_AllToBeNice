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
#ifndef INCLUDE_ATN_GAME_ENEMY_BULLET_DATA
#define INCLUDE_ATN_GAME_ENEMY_BULLET_DATA

#include <glm/glm.hpp>

namespace atn::game::enemy_bullet::data {

inline const float radius{0.025f};

inline const float speed{0.0005f};

inline const glm::vec3 red{static_cast<float>(0xcd) / static_cast<float>(0xff),
                           static_cast<float>(0x33) / static_cast<float>(0xff),
                           static_cast<float>(0x58) / static_cast<float>(0xff)};

inline const glm::vec3 orange{static_cast<float>(0xef) / static_cast<float>(0xff),
                              static_cast<float>(0x7f) / static_cast<float>(0xff),
                              static_cast<float>(0x37) / static_cast<float>(0xff)};

}  // namespace atn::game::enemy_bullet::data

#endif  // !INCLUDE_ATN_GAME_ENEMY_BULLET_DATA