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
#ifndef INCLUDE_ATN_GAME_POD_TRAIL_LOGIC
#define INCLUDE_ATN_GAME_POD_TRAIL_LOGIC

#include "atn/engine/logic/component.h"
#include "atn/game/nier_e_airplane/pod_trail/data.h"

namespace atn::game::pod_trail {

class LogicComponent : public engine::logic::Component {
 public:
  explicit LogicComponent(const glm::vec3 &force);
  virtual ~LogicComponent();

 public:
  virtual void Tick(size_t delta) override;

 private:
  size_t life_{data::life};
  glm::vec3 force_{};
  float speed_{data::speed};
  float rotation_speed_{data::rotation_speed};
  glm::mat4 scale_{1.0f};
};

}  // namespace atn::game::pod_trail

#endif  // !INCLUDE_ATN_GAME_POD_TRAIL_LOGIC
