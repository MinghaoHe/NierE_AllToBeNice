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

#include "system.h"

#include "atn/engine/audio/component.h"
#include "atn/game/game.h"

namespace atn::engine::audio {

System::System() {
  device_id_ = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_OUTPUT, NULL);
  Mix_OpenAudio(device_id_, NULL);

  std::string res_path = game::Bgm();
  if (!res_path.empty()) {
    bgm_ = Mix_LoadMUS(res_path.c_str());
  }
  Mix_PlayMusic(bgm_, -1);
}

System::~System() {
  if (bgm_) {
    Mix_FreeMusic(bgm_);
  }
  Mix_CloseAudio();
  SDL_CloseAudioDevice(device_id_);
}

void System::TickPrev(size_t delta) {}

void System::TickEntity(size_t delta, std::shared_ptr<ecs::Component> component) {
  std::shared_ptr<audio::Component> audio{std::dynamic_pointer_cast<audio::Component>(component)};
  audio->Tick(delta);
}

void System::TickPost(size_t delta) {}

}  // namespace atn::engine::audio
