#include "renderer.hpp"

#include "shader.hpp"

namespace hud {

float vertices[] = {
    // 位置              // 颜色
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // 右下
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // 左下
    0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // 顶部
};

unsigned int indices[] = {
    0,
    1,
    2,  // 第一个三角形
};

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Render() {

  SetBackground();
  shader_->Use();

  glBindVertexArray(vao_);
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

void Renderer::Init(const std::shared_ptr<Shader>& shader) {
  shader_ = shader;

  glGenVertexArrays(1, &vao_);
  glGenBuffers(1, &vbo_);
  glGenBuffers(1, &ebo_);

  glBindVertexArray(vao_);

  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::SetBackground() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

}  // namespace hud