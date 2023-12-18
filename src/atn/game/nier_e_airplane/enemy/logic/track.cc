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

#include "track.h"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>

#include "atn/utils/random.h"

namespace atn::game::enemy::logic {

Track::Track() {}

void Track::SetEnemyTrace(TrackClass track_class,
                          const glm::mat4 &end_model) {
  track_class_ = track_class;
  interval_ = utils::random::UIntPtr() % 40 + 160;
  if (track_class_ == TrackClass::Fixed) {
    target_ = end_model * glm::vec4{0.0f, 0.0f, 0.0f, 0.1f};
  } else if (track_class_ == TrackClass::Moving) {
    target_ = glm::vec3{utils::random::Float() / 10.0f * 9.0f,
                       (utils::random::Float() / 2.0f + 0.3f) / 10.0f * 9.0f, 0.0f};
  }
}

glm::mat4 Track::TrackModel(size_t delta, const glm::mat4 &model) {
  switch (track_class_) {
    case TrackClass::Fixed:
      return FixedTrackModel(delta, model);
    case TrackClass::Moving:
      return MovingTrackModel(delta, model);
    default:
      return glm::mat4{1.0f};
  }
}

glm::mat4 Track::FixedTrackModel(size_t delta, const glm::mat4 &model) { return glm::mat4{1.0f}; }

glm::mat4 Track::MovingTrackModel(size_t delta, const glm::mat4 &model) {
  if (interval_ < delta_) {
    delta_ = 0;
    interval_ = utils::random::UIntPtr() % 50 + 450;
    target_ = glm::vec3{utils::random::Float() / 10.0f * 9.0f,
                  (utils::random::Float() / 2.0f + 0.3f) / 10.0f * 9.0f, 0};
  }
  delta_ += delta;

  glm::vec3 current = model * glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
  glm::vec3 error = current - target_;
  speed_.x = p_v * (p * error.x) + (1.0f - p_v) * speed_.x;
  speed_.y = p_v * (p * error.y) + (1.0f - p_v) * speed_.y;
  speed_.x = std::clamp(speed_.x, -0.05f, 0.05f) / 2.0f;
  speed_.y = std::clamp(speed_.y, -0.05f, 0.05f) / 2.0f;
  return glm::translate(model, glm::vec3{-speed_.x * delta, -speed_.y * delta, 0.0f});
}

}  // namespace atn::game::enemy::logic
