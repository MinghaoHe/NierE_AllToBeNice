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

#if NIER_E_AIRPLANE

#include <fstream>
#include <glm/gtc/matrix_transform.hpp>

#include "atn/engine/world/prime_player.h"
#include "atn/game/nier_e_airplane/game_control.h"
#include "atn/game/nier_e_airplane/nier_e_airplane.h"
#include "atn/game/nier_e_airplane/enemy.h"

namespace atn {

extern std::shared_ptr<game::CtrlBlock> ggame_block_;
extern std::weak_ptr<engine::world::PrimePlayer> gprimer_;

namespace game {

void Tick() {
  static Controller ctrl;
  ctrl.Tick();
}

Controller::Controller() {
  std::ifstream file("conf/enemy.json");
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
  config_ = nlohmann::json::parse(content);
}

Controller::~Controller() {}

void Controller::Tick() {
  if (ggame_block_->emeny_count == ggame_block_->destory_count) {
    std::string level_key = std::to_string(level_);
    if (!config_.contains(level_key)) {
      return;
    }

    std::vector<std::string> enemies = config_[level_key].get<std::vector<std::string>>();
    for (size_t i = 0; i < enemies.size(); ++i) {
      std::shared_ptr<game::enemy::EntityCreateParam> enemy_param{std::make_shared<game::enemy::EntityCreateParam>()};
      enemy_param->text = enemies[i];

      float gap = 2.0f / static_cast<float>(enemies.size() + 1);
      enemy_param->model = glm::translate(enemy_param->model, glm::vec3(-1.0f + gap * (i + 1), 0.5f, 0.0f));
      if (!gprimer_.expired()) {
        gprimer_.lock()->CreateEntity(enemy_param);
      }
    }
    ++level_;
    ggame_block_->emeny_count = enemies.size();
    ggame_block_->destory_count = 0;
  }
}

}  // namespace game

}  // namespace atn

#endif
