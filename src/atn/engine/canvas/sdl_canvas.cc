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

#include "sdl_canvas.h"

#ifdef _MSC_VER
extern "C" {
__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}  // extern "C"
#endif  // _MSC_VER

namespace atn::engine::canvas {

SDLCanvas::SDLCanvas() {
  SDL_Init(SDL_INIT_EVERYTHING);

  SetAttribute();
}

SDLCanvas::~SDLCanvas() {
  SDL_Quit();
}

void SDLCanvas::Create(const canvas::CreateParam &param) {
  name_ = param.name;
  size_ = param.size;

  window_ = SDL_CreateWindow(name_.c_str(), size_.width, size_.height, SDL_WINDOW_OPENGL);
  context_ = SDL_GL_CreateContext(window_);

  SetIcon();
  // SDL_HideCursor();
}

void SDLCanvas::Destroy() {
  SDL_GL_DeleteContext(context_);
  SDL_DestroyWindow(window_);
}

void SDLCanvas::Swap() { SDL_GL_SwapWindow(window_); }

void SDLCanvas::SetAttribute() const {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "best");
}

void SDLCanvas::SetIcon() {
  SDL_Surface *surface{SDL_LoadBMP("res/icon/Nier.bmp")};
  SDL_SetWindowIcon(window_, surface);
  SDL_DestroySurface(surface);
}

}  // namespace atn::engine::canvas
