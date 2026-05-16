#ifndef JOJO_HUD_RENDERER_HPP_
#define JOJO_HUD_RENDERER_HPP_

#include <optional>

#include "context.hpp"

namespace hud {

class Renderer {
 public:
  Renderer();
  ~Renderer();

  void Init(const std::shared_ptr<Shader>& shader);

  void Render();

 private:
  void SetBackground();

 private:
  unsigned int vbo_;  // 顶点缓冲对象
  unsigned int vao_;  // 顶点数组对象
  unsigned int ebo_;  // 索引缓冲对象

  std::optional<unsigned int> texture_;  // 一个纹理对象

  std::shared_ptr<Shader> shader_;
};

}  // namespace hud

#endif