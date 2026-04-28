#include "context.hpp"

#include "process_input.hpp"

namespace hud {

OpenGLContext::OpenGLContext(WindowConfig& cfg) : window_config_(cfg) {}

OpenGLContext::~OpenGLContext() {
  if (init_result_glfw_) {
  }

  if (init_result_glad_) {
  }
}

bool OpenGLContext::Initialize() {
  // 初始化 GLFW
  window_ = InitGlfw();
  if (window_ == nullptr) {
    return false;
  }
  init_result_glfw_ = true;

  // 初始化 GLAD（OpenGL函数指针）
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return false;
  }
  init_result_glad_ = true;

  // 初始化 InputProcessor
  input_processor_ = CreateInputProcessor(window_);
  if (input_processor_ != nullptr) {
  }
  init_result_input_processor_ = true;

  return true;
}

void OpenGLContext::ProcessInput() {
  if (input_processor_) {
    input_processor_->Process();
  }
}

GLFWwindow* OpenGLContext::InitGlfw() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return nullptr;
  }
  glfwMakeContextCurrent(window);
  return window;
}

WindowConfig CreateWindowCfg() {
  WindowConfig cfg;
  cfg.pos_x = 0;
  cfg.pos_y = 0;
  cfg.width = 800;
  cfg.height = 600;

  return cfg;
}

}  // namespace hud