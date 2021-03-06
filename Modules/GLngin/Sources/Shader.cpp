#include "Shader.hpp"

#include "Mat4.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

#include <cstring>

namespace GLngin {

namespace {

void GetErrorInfo(unsigned int id, bool forProgram)
{
    int logLen;
    if (forProgram) {
        GL_CALL(glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLen));
    } else {
        GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen));
    }
    if (logLen > 0) {
        char *log = new char[logLen];
        int written;
        if (forProgram) {
            GL_CALL(glGetProgramInfoLog(id, logLen, &written, &log[0]));
        } else {
            GL_CALL(glGetShaderInfoLog(id, logLen, &written, &log[0]));
        }
        LOG(log);
        delete[] log;
    }
}

unsigned int CreateShader(unsigned int type, const char *src)
{
    unsigned int shaderID;
    GL_CALL(shaderID = glCreateShader(type));
    if (shaderID == 0) {
        LOG("Error occurred during the shader creation");
        return 0;
    }
    GL_CALL(glShaderSource(shaderID, 1, &src, nullptr));
    GL_CALL(glCompileShader(shaderID));
    int OK = 0;
    GL_CALL(glGetShaderiv(shaderID, GL_COMPILE_STATUS, &OK));
    if (OK == 0) {
        LOG(std::string("Error occurred during the compilation of \'") + std::string(src) + std::string("\'"));
        GetErrorInfo(shaderID, false);
        GL_CALL(glDeleteShader(shaderID));
        return 0;
    }
    return shaderID;
}

}  // namespace

Shader::Shader()
    : m_id(0)
{
}

Shader::~Shader()
{
    GL_CALL(glDeleteProgram(m_id));
}

void Shader::Init(const std::optional<std::string> &vertexShaderSource,
                  const std::optional<std::string> &geometryShaderSource,
                  const std::optional<std::string> &tessControlShaderSource,
                  const std::optional<std::string> &tessEvalShaderSource,
                  const std::optional<std::string> &fragmentShaderSource,
                  const std::optional<std::string> &computeShaderSource)
{
    GL_CALL(m_id = glCreateProgram());
    if (m_id == 0) {
        LOG("Error in shader program creation.");
        return;
    }

    unsigned int shaders[6];
    memset(shaders, 0, sizeof(shaders));

    for (size_t i = 0; i < 6; ++i) {
        unsigned int type;
        std::optional<std::string> source;
        switch (i) {
            case 0:
                type = GL_VERTEX_SHADER;
                source = vertexShaderSource;
                break;
            case 1:
                type = GL_GEOMETRY_SHADER;
                source = geometryShaderSource;
                break;
            case 2:
                type = GL_TESS_CONTROL_SHADER;
                source = tessControlShaderSource;
                break;
            case 3:
                type = GL_TESS_EVALUATION_SHADER;
                source = tessEvalShaderSource;
                break;
            case 4:
                type = GL_FRAGMENT_SHADER;
                source = fragmentShaderSource;
                break;
            case 5:
                type = GL_COMPUTE_SHADER;
                source = computeShaderSource;
                break;
        }
        if (source) {
            shaders[i] = CreateShader(type, source.value().c_str());
            if (shaders[i] != 0) {
                GL_CALL(glAttachShader(m_id, shaders[i]));
            }
        }
    }

    GL_CALL(glLinkProgram(m_id));
    for (unsigned int shaderID : shaders) {
        if (shaderID != 0) {
            GL_CALL(glDetachShader(m_id, shaderID));
            GL_CALL(glDeleteShader(shaderID));
        }
    }
    int OK = 0;
    GL_CALL(glGetProgramiv(m_id, GL_LINK_STATUS, &OK));
    if (OK == 0) {
        LOG("Failed to link shader program!");
        GetErrorInfo(m_id, true);
    }
}

void Shader::Bind() const
{
    GL_CALL(glUseProgram(m_id));
}

void Shader::UnBind() const
{
    GL_CALL(glUseProgram(0));
}

unsigned int Shader::GetID() const
{
    return m_id;
}

void Shader::SetUniformFloat(const char *uniformName, float value)
{
    GL_CALL(glUniform1f(GetUniformLocation(uniformName), value));
}

void Shader::SetUniformInt(const char *uniformName, int value)
{
    GL_CALL(glUniform1i(GetUniformLocation(uniformName), value));
}

void Shader::SetUniformMat4(const char *uniformName, const Math::Mat4 &value)
{
    GL_CALL(glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_TRUE, value));
}

void Shader::SetUniformVec2(const char *uniformName, const Math::Vec2 &value)
{
    GL_CALL(glUniform2f(GetUniformLocation(uniformName), value.x, value.y));
}

void Shader::SetUniformVec3(const char *uniformName, const Math::Vec3 &value)
{
    GL_CALL(glUniform3f(GetUniformLocation(uniformName), value.x, value.y, value.z));
}

void Shader::SetUniformVec4(const char *uniformName, const Math::Vec4 &value)
{
    GL_CALL(glUniform4f(GetUniformLocation(uniformName), value.x, value.y, value.z, value.w));
}

void Shader::SetUniformTexture2D(const char *uniformName, unsigned int texID, unsigned int unitID)
{
    GL_CALL(glActiveTexture(GL_TEXTURE0 + unitID));
    GL_CALL(glBindTexture(GL_TEXTURE_2D, texID));
    GL_CALL(glUniform1i(GetUniformLocation(uniformName), unitID));
}

void Shader::SetUniformTextureCube(const char *uniformName, unsigned int texID, unsigned int unitID)
{
    GL_CALL(glActiveTexture(GL_TEXTURE0 + unitID));
    GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, texID));
    GL_CALL(glUniform1i(GetUniformLocation(uniformName), unitID));
}

int Shader::GetAttributeLocation(const char *attribName)
{
    if (auto it = attributeLocationCache.find(attribName); it != attributeLocationCache.end()) {
        return it->second;
    }

    GL_CALL(attributeLocationCache[attribName] = glGetAttribLocation(m_id, attribName));
    return attributeLocationCache[attribName];
}

int Shader::GetUniformLocation(const char *uniformName)
{
    if (auto it = uniformLocationCache.find(uniformName); it != uniformLocationCache.end()) {
        return it->second;
    }

    GL_CALL(uniformLocationCache[uniformName] = glGetUniformLocation(m_id, uniformName));
    return uniformLocationCache[uniformName];
}

}  // namespace GLngin
