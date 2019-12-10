#pragma once

#ifndef GLNGIN_SHADER_HPP
#define GLNGIN_SHADER_HPP

#include "API.hpp"
#include <string>
#include <unordered_map>
#include <optional>

namespace GLngin {
namespace Math {
class Mat4;
class Vec2;
class Vec3;
class Vec4;
}  // namespace Math

class GLNGIN_API Shader final {
public:
    Shader();
    ~Shader();

    Shader(const Shader &) = delete;
    Shader &operator=(const Shader &) = delete;

    void Init(const std::optional<std::string> &vertexShaderFile, const std::optional<std::string> &geometryShaderFile,
              const std::optional<std::string> &tessControlShaderFile,
              const std::optional<std::string> &tessEvalShaderFile,
              const std::optional<std::string> &fragmentShaderFile,
              const std::optional<std::string> &computeShaderFile);

    void Bind() const;
    void UnBind() const;

    unsigned int GetID() const;

    void SetUniformFloat(const char *uniformName, float value);
    void SetUniformInt(const char *uniformName, int value);
    void SetUniformMat4(const char *uniformName, const Math::Mat4 &value);
    void SetUniformVec2(const char *uniformName, const Math::Vec2 &value);
    void SetUniformVec3(const char *uniformName, const Math::Vec3 &value);
    void SetUniformVec4(const char *uniformName, const Math::Vec4 &value);
    void SetUniformTexture2D(const char *uniformName, unsigned int texID, unsigned int unitID);
    void SetUniformTextureCube(const char *uniformName, unsigned int texID, unsigned int unitID);

    int GetAttributeLocation(const char *attribName);
    int GetUniformLocation(const char *uniformName);

private:
    unsigned int m_id;
    std::unordered_map<std::string, int> uniformLocationCache;
    std::unordered_map<std::string, int> attributeLocationCache;
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_SHADER_HPP
