#ifndef JOJO_HUD_RENDERER_HPP_
#define JOJO_HUD_RENDERER_HPP_

#include "context.hpp"

namespace hud {

class Renderer {
 public:
  Renderer();
  ~Renderer();

  void Render();
};

}  // namespace hud

#endif