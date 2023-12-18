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
#ifndef INCLUDE_ATN_GAME_ENEMY_LOGIC
#define INCLUDE_ATN_GAME_ENEMY_LOGIC

#include "atn/engine/logic/component.h"

#include "atn/game/nier_e_airplane/enemy/data.h"
#include "atn/game/nier_e_airplane/enemy/logic/shoot.h"
#include "atn/game/nier_e_airplane/enemy/logic/track.h"

namespace atn::game::enemy {

struct LogicCreateParam {
  std::string text;
  float scale{data::scale};
  logic::TrackClass track_class{logic::TrackClass::Moving};
};

class LogicComponent : public engine::logic::Component {
 public:
  explicit LogicComponent(const LogicCreateParam &create_param);
  virtual ~LogicComponent();

 public:
  virtual void Tick(size_t delta) override;

 private:
  void Shoot(size_t delta);
  void UnderAttack(size_t delta);

 private:
  std::string text_;
  float height_{};
  float width_{};
  float scale_{};

  size_t shoot_delta_{};
  const size_t shoot_cooldown_{data::shoot_cooldown};

  bool collision_{};
  int life_{20};
  size_t shake_delta_{};

  logic::Track track_;
  logic::Shoot shoot_;
};

}  // namespace atn::game::enemy

#endif  // !INCLUDE_ATN_GAME_ENEMY_LOGIC
