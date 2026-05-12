#ifndef JOJO_HUD_OPENGLCONTEXT_HPP_
#define JOJO_HUD_OPENGLCONTEXT_HPP_

#include "glad/glad.h"
// 必须在包含 glad.h 之后
#include <iostream>
#include <memory>

#include "GLFW/glfw3.h"

namespace hud {

/// @brief 窗口配置信息
struct WindowConfig {
  int pos_x;
  int pos_y;
  int width;
  int height;
};

WindowConfig CreateWindowCfg();

class InputProcessor;
class Renderer;
class Shader;
class OpenGLContext {
 public:
  OpenGLContext(WindowConfig& cfg);
  ~OpenGLContext();
  /// @brief
  /// @return
  bool Initialize();

  GLFWwindow* GetWindow() { return window_; }

  void ProcessInput();
  void Render();

 private:
  /// @brief 初始化 GLFW
  GLFWwindow* InitGlfw();

 private:
  bool init_result_glfw_{false};             // GLFW 初始化结果
  bool init_result_glad_{false};             // GLAD 初始化结果
  bool init_result_input_processor_{false};  // InputPocessor 初始化结果
  bool init_result_renderer_{false};         // Renderer 初始化结果
  bool init_result_shader_{false};           // Shader 初始化结果

  WindowConfig window_config_;
  GLFWwindow* window_{nullptr};

  std::unique_ptr<InputProcessor> input_processor_;
  std::unique_ptr<Renderer> renderer_;
  std::shared_ptr<Shader> shader_;

  std::string vert_shader_path_{"shaders/vert.shader"};
  std::string frag_shader_path_{"shaders/frag.shader"};
};
}  // namespace hud

#endif  // !JOJO_HUD_OPENGLCONTEXT_HPP_