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
#ifndef INCLUDE_ATN_GAME_ENEMY_LOGIC_TRACK
#define INCLUDE_ATN_GAME_ENEMY_LOGIC_TRACK

#include <glm/glm.hpp>

namespace atn::game::enemy::logic {

enum class TrackClass { Fixed, Moving };

class Track {
 public:
  Track();

 public:
  void SetEnemyTrace(TrackClass track_class,
                     const glm::mat4 &end_model = glm::mat4{1.0f});

  glm::mat4 TrackModel(size_t delta, const glm::mat4 &model);

 private:
  glm::mat4 FixedTrackModel(size_t delta, const glm::mat4 &model);
  glm::mat4 MovingTrackModel(size_t delta, const glm::mat4 &model);

 private:
  TrackClass track_class_{TrackClass::Moving};

  size_t delta_{};
  size_t interval_{};
  glm::vec3 target_{};
  glm::vec2 speed_{};
  float p{0.5};
  float p_v{0.0015};
};

}  // namespace atn::game::enemy::logic

#endif  // !INCLUDE_ATN_GAME_ENEMY_LOGIC_TRACK
