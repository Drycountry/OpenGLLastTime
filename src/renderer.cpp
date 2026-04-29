#include "renderer.hpp"

namespace hud {

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Render() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

}  // namespace hud