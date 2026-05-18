#include "texture_loader.hpp"

#include "context.hpp"
#include "stb_image.h"

namespace hud {

/// @brief 加载纹理，返回纹理ID
/// @param path 纹理路径
/// @return 纹理ID
std::optional<unsigned int> LoadTexture(const std::string& path) {
  // 加载纹理文件到内存 data
  int width, height, nr_channels;
  stbi_set_flip_vertically_on_load(true);

  unsigned char* data = stbi_load(path.data(), &width, &height, &nr_channels, 0);
  if (data == nullptr) {  // 加载文件失败
    return std::nullopt;
  }

  // 声明纹理
  unsigned int texture;
  glGenTextures(1, &texture);

  // 绑定纹理
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // 生成纹理（当前绑定的纹理对象会被附加上纹理图像）
  glTexImage2D(GL_TEXTURE_2D,  // 指定纹理目标，限于 GL_TEXTURE_2D，1D、3D不会受影响
               0,              // 多级渐远纹理的级别（此处为基本级别）
               GL_RGB,         // 告诉OpenGL我们希望把纹理储存为何种格式
               width,          // 设置纹理宽度（此处与图像宽度相同）
               height,
               0,       // 总是被设为0（历史遗留的问题）
               GL_RGB,  // 源图的格式和数据类型
               GL_UNSIGNED_BYTE,
               data  // 图像数据指针
  );
  glGenerateMipmap(GL_TEXTURE_2D);  // 由 OpenGL 自动生成多级渐远纹理（mipmap）

  // 释放内存
  stbi_image_free(data);

  return texture;
}

/// @brief 加载纹理，返回纹理ID
/// @param path 纹理路径
/// @return 纹理ID
std::optional<unsigned int> LoadTextureRgba(const std::string& path) {
  // 加载纹理文件到内存 data
  int width, height, nr_channels;
  stbi_set_flip_vertically_on_load(true);
  unsigned char* data = stbi_load(path.data(), &width, &height, &nr_channels, 0);
  if (data == nullptr) {  // 加载文件失败
    return std::nullopt;
  }

  // 声明纹理
  unsigned int texture;
  glGenTextures(1, &texture);

  // 绑定纹理
  glBindTexture(GL_TEXTURE_2D, texture);
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // 生成纹理（当前绑定的纹理对象会被附加上纹理图像）
  glTexImage2D(GL_TEXTURE_2D,  // 指定纹理目标，限于 GL_TEXTURE_2D，1D、3D不会受影响
               0,              // 多级渐远纹理的级别（此处为基本级别）
               GL_RGB,         // 告诉OpenGL我们希望把纹理储存为何种格式
               width,          // 设置纹理宽度（此处与图像宽度相同）
               height,
               0,        // 总是被设为0（历史遗留的问题）
               GL_RGBA,  // 源图的格式和数据类型
               GL_UNSIGNED_BYTE,
               data  // 图像数据指针
  );
  glGenerateMipmap(GL_TEXTURE_2D);  // 由 OpenGL 自动生成多级渐远纹理（mipmap）

  // 释放内存
  stbi_image_free(data);

  return texture;
}

}  // namespace hud