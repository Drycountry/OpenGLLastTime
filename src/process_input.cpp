#include "process_input.hpp"

namespace hud {

InputProcessor::InputProcessor() {}

InputProcessor::~InputProcessor() {}

bool InputProcessor::Initialize(GLFWwindow* win) {
  window_ = win;
  return win != nullptr;
}

void InputProcessor::Process() {
  if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window_, true);
  }
}

std::unique_ptr<InputProcessor> CreateInputProcessor(GLFWwindow* win) {
  auto uptr = std::make_unique<InputProcessor>();
  if (uptr->Initialize(win) == true) {
    return uptr;
  } else {
    return nullptr;
  }
}

}  // namespace hud