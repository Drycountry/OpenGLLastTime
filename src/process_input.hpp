#ifndef JOJO_HUD_PROCESS_INPUT_HPP_
#define JOJO_HUD_PROCESS_INPUT_HPP_

#include <memory>

#include "context.hpp"

namespace hud {

/// @brief 输入处理器
class InputProcessor {
 public:
  InputProcessor();
  ~InputProcessor();
  bool Initialize(GLFWwindow* win);
  void Process();

 private:
  GLFWwindow* window_{nullptr};
};

/// @brief 创建输入处理器
/// @param win 窗口指针
std::unique_ptr<InputProcessor> CreateInputProcessor(GLFWwindow* win);

}  // namespace hud

#endif  // !JOJO_HUD_PROCESS_INPUT_HPP_