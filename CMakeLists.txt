cmake_minimum_required(VERSION 3.20)
project(OpenGL202604)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
  "src/main.cpp"
  "src/context.cpp"
  "src/renderer.cpp"
  "src/shader.cpp"
  "src/process_input.cpp"
  "src/callbacks.cpp"
  "src/texture_loader.cpp"

  "3rdparty/glad/src/glad.c"
  "3rdparty/stb/src/stb_image.cpp"
)

# 第三方库 OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME}
  PRIVATE ${OPENGL_LIBRARIES}
)

# 第三方库 GLAD
set(LibGladPath ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glad)
target_include_directories(${PROJECT_NAME}
  PRIVATE ${LibGladPath}/include
)

# 第三方库 GLFW
set(LibGlfwPath ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/GLFW)
target_include_directories(${PROJECT_NAME}
  PRIVATE ${LibGlfwPath}/include
)
target_link_libraries(${PROJECT_NAME} PRIVATE
  optimized  ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/GLFW/lib/glfw3-release.lib
  debug  ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/GLFW/lib/glfw3-debug.lib
)

# 第三方库 stb_image
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/stb/include)

# 第三方库 glm
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm/include)

# 构建时拷贝资源文件夹 res 到构建目录
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
  COMMENT "Copying shaders to output directory"
)