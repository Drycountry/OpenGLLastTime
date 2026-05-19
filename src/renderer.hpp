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
  void InitHud(const std::shared_ptr<Shader>& hud_shader);

  void Render();

 private:
  void SetBackground();
  void RenderVelocityVector();

 private:
  unsigned int vbo_;  // 顶点缓冲对象
  unsigned int vao_;  // 顶点数组对象
  unsigned int ebo_;  // 索引缓冲对象

  // HUD 速度矢量符号
  unsigned int hud_vao_;
  unsigned int hud_vbo_;
  unsigned int hud_circle_vertex_count_;
  unsigned int hud_line_vertex_count_;

  std::optional<unsigned int> texture_1_;  // 一个纹理对象
  std::optional<unsigned int> texture_2_;  // 一个纹理对象

  std::shared_ptr<Shader> shader_;
  std::shared_ptr<Shader> hud_shader_;
};

}  // namespace hud

#endif