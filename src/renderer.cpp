#include "renderer.hpp"

#include <cmath>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.hpp"
#include "texture_loader.hpp"

namespace hud {

float vertices[] = {
    // positions          // colors           // texture coords
    0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // top right
    0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom left
    -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // top left
};

unsigned int indices[] = {
    0, 1, 3,  // 第一个三角形
    1, 2, 3   // 第二个三角形
};

// 纹理坐标
float texCoords[] = {
    0.0f, 0.0f,  // 左下角
    1.0f, 0.0f,  // 右下角
    0.5f, 1.0f   // 上中
};

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::Render() {
  SetBackground();
  shader_->Use();

  // bind texture
  if (texture_1_.has_value()) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_1_.value());
  }
  if (texture_2_.has_value()) {
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture_2_.value());
  }

  glUniform1i(glGetUniformLocation(shader_->Id(), "texture1"), 0);
  glUniform1i(glGetUniformLocation(shader_->Id(), "texture2"), 1);

  // 变换矩阵
  glm::mat4 transform = glm::mat4(1.0f);
  transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
  transform = glm::rotate(transform, static_cast<float>(glm::radians(glfwGetTime())), glm::vec3(0.0, 0.0, 1.0));
  auto uniform_loc_transform = glGetUniformLocation(shader_->Id(), "transform");
  glUniformMatrix4fv(uniform_loc_transform, 1, GL_FALSE, glm::value_ptr(transform));

  glBindVertexArray(vao_);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  // 绘制速度矢量符号（HUD 叠加层）
  RenderVelocityVector();
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
  }

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // 加载纹理
  texture_1_ = LoadTexture("res/textures/container.jpg");
  texture_2_ = LoadTextureRgba("res/textures/awesomeface.png");
}

void Renderer::InitHud(const std::shared_ptr<Shader>& hud_shader) {
  hud_shader_ = hud_shader;

  // SVG viewBox 300×205 → NDC 映射，以圆心 (150,150) 为原点
  const float scale = 0.002f;  // 300 SVG 单位 → 0.6 NDC 宽度

  std::vector<float> vertices;

  // ── 圆形（LINE_LOOP）──
  const int circle_segments = 64;
  const float radius = 50.0f * scale;  // 0.1 NDC
  for (int i = 0; i < circle_segments; ++i) {
    float angle = 2.0f * 3.14159265f * i / circle_segments;
    vertices.push_back(radius * std::cos(angle));
    vertices.push_back(radius * std::sin(angle));
  }
  hud_circle_vertex_count_ = circle_segments;

  // ── 三条直线（LINES：每对顶点一条线段）──
  // 左侧翼: (-0.3, 0) → (-0.1, 0)
  vertices.push_back(-0.3f); vertices.push_back(0.0f);
  vertices.push_back(-0.1f); vertices.push_back(0.0f);
  // 右侧翼: (0.1, 0) → (0.3, 0)
  vertices.push_back(0.1f);  vertices.push_back(0.0f);
  vertices.push_back(0.3f);  vertices.push_back(0.0f);
  // 顶部竖线: (0, 0.3) → (0, 0.1)
  vertices.push_back(0.0f);  vertices.push_back(0.3f);
  vertices.push_back(0.0f);  vertices.push_back(0.1f);

  hud_line_vertex_count_ = 6;

  glGenVertexArrays(1, &hud_vao_);
  glGenBuffers(1, &hud_vbo_);

  glBindVertexArray(hud_vao_);
  glBindBuffer(GL_ARRAY_BUFFER, hud_vbo_);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::RenderVelocityVector() {
  if (!hud_shader_) return;

  hud_shader_->Use();

  // 左上 ↔ 右下 循环平移
  float t = static_cast<float>(glfwGetTime());
  float offset = std::sin(t * 0.8f) * 0.55f;
  glUniform2f(glGetUniformLocation(hud_shader_->Id(), "uTranslate"), offset, -offset);

  // 宽高比修正：视口 800×600 → 0.75，保证圆形不变形
  glUniform1f(glGetUniformLocation(hud_shader_->Id(), "uAspectRatio"), 600.0f / 800.0f);

  glBindVertexArray(hud_vao_);

  glLineWidth(3.0f);  // 加粗线条，模拟 SVG stroke-width

  // 绘制圆形
  glDrawArrays(GL_LINE_LOOP, 0, hud_circle_vertex_count_);

  // 绘制三条直线
  glDrawArrays(GL_LINES, hud_circle_vertex_count_, hud_line_vertex_count_);

  glBindVertexArray(0);
}

void Renderer::SetBackground() {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

}  // namespace hud