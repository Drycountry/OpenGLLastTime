#include <optional>
#include <string>

namespace hud {

/// @brief 加载纹理，返回纹理ID
/// @param path 纹理路径
/// @return 纹理ID
std::optional<unsigned int> LoadTexture(const std::string& path);

/// @brief 加载纹理，返回纹理ID
/// @param path 纹理路径
/// @return 纹理ID
std::optional<unsigned int> LoadTextureRgba(const std::string& path);

}  // namespace hud