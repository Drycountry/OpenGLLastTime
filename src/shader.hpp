#ifndef JOJO_HUD_SHADER_HPP_
#define JOJO_HUD_SHADER_HPP_

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace hud {

class Shader {
 public:
  /// @brief 构造函数
  Shader();

  /// @brief 析构函数
  ~Shader();

  /// @brief 初始化
  /// @param vertexPath 顶点着色器文件路径
  /// @param fragmentPath 片段着色器文件路径
  /// @return true 成功，false 失败
  bool Init(const std::string& vertexPath, const std::string& fragmentPath);

  /// @brief 获取当前着色器程序 id
  unsigned int Id() const { return id_; }

  /// @brief 激活/使用着色器程序
  void Use() { glUseProgram(id_); }

  /// @brief 设置 bool 类型 uniform
  void SetBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(id_, name.c_str()), (int)value);
  }

  /// @brief 设置 int 类型 uniform
  void SetInt(const std::string& name, int value) const { glUniform1i(glGetUniformLocation(id_, name.c_str()), value); }

  /// @brief 设置 float 类型 uniform
  void SetFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
  }

 private:
  /// @brief utility function for checking shader compilation/linking errors.
  void CheckCompileErrors(unsigned int shader, std::string type);

 private:
  unsigned int id_;  // 着色器程序 id

  std::string vert_shader_path_{};
  std::string frag_shader_path_{};
};

}  // namespace hud

#endif  // !JOJO_HUD_SHADER_HPP_