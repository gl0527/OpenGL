#pragma once

#ifndef GLNGIN_SHADER_HPP
#define GLNGIN_SHADER_HPP

#include "API.hpp"
#include "Debug.hpp"
#include <GL/glew.h>
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

    void Init(const std::optional<std::string> &vertexShaderSource,
              const std::optional<std::string> &geometryShaderSource,
              const std::optional<std::string> &tessControlShaderSource,
              const std::optional<std::string> &tessEvalShaderSource,
              const std::optional<std::string> &fragmentShaderSource,
              const std::optional<std::string> &computeShaderSource);

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

    template <const size_t N>
    void SetUniformFloatArray(const char *uniformName, const float (&v)[N]);
    template <const size_t N>
    void SetUniformIntArray(const char *uniformName, const int (&v)[N]);
    template <const size_t N>
    void SetUniformVec2Array(const char *uniformName, const Math::Vec2 (&v)[N]);
    template <const size_t N>
    void SetUniformVec3Array(const char *uniformName, const Math::Vec3 (&v)[N]);
    template <const size_t N>
    void SetUniformVec4Array(const char *uniformName, const Math::Vec4 (&v)[N]);

    int GetAttributeLocation(const char *attribName);
    int GetUniformLocation(const char *uniformName);

private:
    unsigned int m_id;
    std::unordered_map<std::string, int> uniformLocationCache;
    std::unordered_map<std::string, int> attributeLocationCache;
};

template <const size_t N>
void Shader::SetUniformFloatArray(const char *uniformName, const float (&v)[N])
{
    GL_CALL(glUniform1fv(GetUniformLocation(uniformName), N, v));
}

template <const size_t N>
void Shader::SetUniformIntArray(const char *uniformName, const int (&v)[N])
{
    GL_CALL(glUniform1iv(GetUniformLocation(uniformName), N, v));
}

template <const size_t N>
void Shader::SetUniformVec2Array(const char *uniformName, const Math::Vec2 (&v)[N])
{
    GL_CALL(glUniform2fv(GetUniformLocation(uniformName), N, &(v[0].x)));
}

template <const size_t N>
void Shader::SetUniformVec3Array(const char *uniformName, const Math::Vec3 (&v)[N])
{
    GL_CALL(glUniform3fv(GetUniformLocation(uniformName), N, &(v[0].x)));
}

template <const size_t N>
void Shader::SetUniformVec4Array(const char *uniformName, const Math::Vec4 (&v)[N])
{
    GL_CALL(glUniform4fv(GetUniformLocation(uniformName), N, &(v[0].x)));
}

}  // namespace GLngin

#endif  // #ifndef GLNGIN_SHADER_HPP
