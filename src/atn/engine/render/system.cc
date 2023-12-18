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

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include "atn/engine/render/component.h"
#include "atn/engine/render/pass/bloom.h"
#include "atn/engine/render/pass/fade.h"
#include "atn/engine/render/pass/normal.h"
#include "atn/engine/render/pass/particles.h"
#include "atn/engine/render/pass/text.h"

std::weak_ptr<atn::engine::render::Text> gtext_render;

namespace atn::engine::render {

System::System(std::shared_ptr<canvas::SDLCanvas> canvas) : canvas_(canvas) {
  gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));

  canvas_frame_ = std::make_unique<CanvasFrame>();
  main_frame_ = std::make_shared<Framebuffer>(canvas_->Size().width,
                                              canvas_->Size().height);
  text_render_ = std::make_shared<Text>();
  gtext_render = text_render_;

  InitPasses();

  // AntiAliasing();
  glViewport(0, 0, canvas_->Size().width, canvas_->Size().height);

  glEnable(GL_DEPTH_TEST);
}

System::~System() {}

void System::TickPrev(size_t delta) {
  ClearFrames();

  for (auto &pass : render_passes_ | std::views::values) {
    pass->PrevDraw(delta);
  }
}

void System::TickEntity(size_t delta, std::shared_ptr<ecs::Component> component) {
  std::shared_ptr<render::Component> render{std::dynamic_pointer_cast<render::Component>(component)};
  const std::string &tag{render->Tag()};

  render->Tick(delta);
  for (auto &pass_data : render->PassQueue()) {
    render_passes_[pass_data->pass_class]->Draw(tag, pass_data, delta);
  }
}

void System::TickPost(size_t delta) {
  std::vector<GLuint> textures{main_frame_->Texture(0)};
  for (auto &pass : render_passes_ | std::views::values) {
    GLuint texture{pass->PostDraw(delta)};
    if (texture != 0) textures.push_back(texture);
  }

  canvas_frame_->Draw(textures);

  canvas_->Swap();
}

void System::InitPasses() {
  render_passes_[PassClass::kNormal] = std::make_unique<NormalPass>(main_frame_);
  render_passes_[PassClass::kText] = std::make_unique<TextPass>(main_frame_);
  render_passes_[PassClass::kFade] = std::make_unique<FadePass>(main_frame_);
  render_passes_[PassClass::kBloom] = std::make_unique<BloomPass>(main_frame_);
  render_passes_[PassClass::kParticles] = std::make_unique<ParticlesPass>(main_frame_);
}

void System::AntiAliasing() {
  glEnable(GL_MULTISAMPLE);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_POLYGON_SMOOTH);
}

void System::ClearFrames() {
  canvas_frame_->Clear();
  main_frame_->Clear();
}

}  // namespace atn::engine::render
