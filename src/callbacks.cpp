#include "callbacks.hpp"

namespace hud::cb {

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }

}  // namespace hud::cb
