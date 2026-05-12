#include "callbacks.hpp"
#include "context.hpp"
#include "process_input.hpp"
#include "renderer.hpp"

int main() {
  auto win_cfg = hud::CreateWindowCfg();
  hud::OpenGLContext context{win_cfg};
  if (context.Initialize() == false) {
    return -1;
  }
  GLFWwindow* window = context.GetWindow();

  // 视口配置
  glViewport(win_cfg.pos_x, win_cfg.pos_y, win_cfg.width, win_cfg.height);
  glfwSetFramebufferSizeCallback(window, hud::cb::FrameBufferSizeCallback);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // 线框模式绘图

  // 主循环/游戏循环
  while (!glfwWindowShouldClose(window)) {
    // 处理输入
    context.ProcessInput();

    // 渲染
    context.Render();

    // 检查并调用事件，交换缓冲
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}