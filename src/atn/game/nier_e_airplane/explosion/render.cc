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

#include "render.h"

#include "atn/engine/render/define.h"
#include "atn/game/nier_e_airplane/explosion/data.h"
#include "atn/utils/random.h"

namespace atn::game::explosion {

RenderComponent::RenderComponent(Type type) : type_(type) {
  std::shared_ptr<engine::render::ParticlesPassData> particle_pass_data{std::make_shared<engine::render::ParticlesPassData>()};
  particle_pass_data->draw_mode = GL_POINTS;
  pass_data_.push_back(particle_pass_data);
}

RenderComponent::~RenderComponent() {}

void RenderComponent::Tick(size_t delta) {
  for (auto data : pass_data_) {
    data->model = seed_->model;
    if (data->pass_class == engine::render::PassClass::kParticles) {
      auto particle_pass_data = std::static_pointer_cast<engine::render::ParticlesPassData>(data);
      if (seed_->logic.contains("duration")) {
        size_t duration{ seed_->logic["duration"].get<size_t>() };
        particle_pass_data->duration = duration;
      }
      if (particle_pass_data->particles.empty()) {
        size_t particle_count = type_ == Type::kHit ? data::kHitCount : data::kDestroyCount;
        float particle_life = type_ == Type::kHit ? data::kHitLife : data::kDestroyLife;
        std::vector<engine::render::Particle> particles;
        for (size_t i = 0; i < particle_count; ++i) {
          particles.emplace_back(engine::render::Particle{
            .life{particle_life},
            .size{utils::random::Float() * 3.0f + 1.0f},
            .velocity = glm::vec3{utils::random::Float() * 0.005f + 0.001f, utils::random::Float() * 0.005f + 0.001f, 0.0f},
            .color = glm::vec3{1.0f},
          });
        }
        particle_pass_data->particles = std::move(particles);
        particle_pass_data->indices.assign_range(std::views::iota(1) | std::views::take(particle_count));
      }
    }
  }
}

}  // namespace atn::game::explosion
