#include "Program.hpp"

#include "Debug.hpp"
#include "Mat4.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

#include <GL/glew.h>
#include <fstream>


namespace GLngin {

namespace {

void GetShaderErrorInfo (unsigned int id)
{
    int logLen;
    GL_CALL (glGetShaderiv (id, GL_INFO_LOG_LENGTH, &logLen));
    if (logLen > 0) {
        char * log = new char[logLen];
        int written;
        GL_CALL (glGetShaderInfoLog (id, logLen, &written, &log[0]));
        LOG (log);
        delete[] log;
    }
}


void GetProgramErrorInfo (unsigned int id)
{
    int logLen;
    GL_CALL (glGetProgramiv (id, GL_INFO_LOG_LENGTH, &logLen));
    if (logLen > 0) {
        char * log = new char[logLen];
        int written;
        GL_CALL (glGetProgramInfoLog (id, logLen, &written, &log[0]));
        LOG (log);
        delete[] log;
    }
}

}   // namepace


Program::Program () :
    m_id (0),
    m_inited (false),
    m_linked (false)
{
}


Program::~Program ()
{
    if (!m_inited)
        return;

    for (const auto& s : m_shaders)
        GL_CALL (glDetachShader (m_id, s));

    m_shaders.clear ();

    GL_CALL (glDeleteProgram (m_id));
}


void Program::Init ()
{
    GL_CALL (m_id = glCreateProgram ());
    if (m_id == 0)
        LOG ("Error in shader program creation.");

    m_inited = true;
}


bool Program::AddShaderFromFile (unsigned int type, const char * fileName)
{
    if (!m_inited || m_linked)
        return false;

    unsigned int loadedShaderID = LoadShaderFromFile (type, fileName);
    if (loadedShaderID == 0)
        return false;

    m_shaders.push_back (loadedShaderID);
    GL_CALL (glAttachShader (m_id, loadedShaderID));
    return true;
}


bool Program::AddShaderFromFile (unsigned int type, const std::string& fileName)
{
    return AddShaderFromFile (type, fileName.c_str ());
}


bool Program::AddShaderFromString (unsigned int type, const char * content)
{
    if (!m_inited || m_linked)
        return false;

    unsigned int loadedShaderID = LoadShaderFromString (type, content);
    if (loadedShaderID == 0)
        return false;

    m_shaders.push_back (loadedShaderID);
    GL_CALL (glAttachShader (m_id, loadedShaderID));
    return true;
}


bool Program::AddShaderFromString (unsigned int type, const std::string& content)
{
    return AddShaderFromString (type, content.c_str ());
}


bool Program::BindAttribIndex (const char * attribName, unsigned int index) const
{
    if (!m_inited || m_linked)
        return false;

    GL_CALL (glBindAttribLocation (m_id, index, attribName));
    return true;
}


bool Program::BindFragDataIndex (const char * attribName, unsigned int index) const
{
    if (!m_inited || m_linked)
        return false;

    GL_CALL (glBindFragDataLocation (m_id, index, attribName));
    return true;
}


bool Program::Link ()
{
    if (!m_inited)
        return false;

    GL_CALL (glLinkProgram (m_id));
    int OK = 0;
    GL_CALL (glGetProgramiv (m_id, GL_LINK_STATUS, &OK));
    if (OK == 0) {
        LOG ("Failed to link shader program!");
        GetProgramErrorInfo (m_id);
        return false;
    }
    m_linked = true;
    return true;
}


bool Program::Use () const
{
    if (!m_linked)
        return false;

    GL_CALL (glUseProgram (m_id));
    return true;
}


void Program::UnUse () const
{
    GL_CALL (glUseProgram (0));
}


unsigned int Program::GetID () const
{
    return m_id;
}


bool Program::SetUniformFloat (const char * uniformName, float value) const
{    
    int location = GetUniformIndex (uniformName);
    if (location < 0)
        return false;
    GL_CALL (glUniform1f (location, value));
    return true;
}


bool Program::SetUniformInt (const char * uniformName, int value) const
{
    int location = GetUniformIndex (uniformName);
    if (location < 0)
        return false;
    GL_CALL (glUniform1i (location, value));
    return true;
}


bool Program::SetUniformMat4 (const char * uniformName, const Math::Mat4& value) const
{
    int location = GetUniformIndex (uniformName);
    if (location < 0)
        return false;
    GL_CALL (glUniformMatrix4fv (location, 1, GL_TRUE, value));
    return true;
}


bool Program::SetUniformVec3 (const char * uniformName, const Math::Vec3& value) const
{
    int location = GetUniformIndex (uniformName);
    if (location < 0)
        return false;
    GL_CALL (glUniform3f (location, value.x, value.y, value.z));
    return true;
}


bool Program::SetUniformVec4 (const char * uniformName, const Math::Vec4& value) const
{
    int location = GetUniformIndex (uniformName);
    if (location < 0)
        return false;
    GL_CALL (glUniform4f (location, value.x, value.y, value.z, value.w));
    return true;
}


bool Program::SetUniformTexture2D (const char * uniformName, unsigned int texID, unsigned int unitID) const
{
    int location = GetUniformIndex (uniformName);
    if (location < 0)
        return false;

    GL_CALL (glActiveTexture (GL_TEXTURE0 + unitID));
    GL_CALL (glBindTexture (GL_TEXTURE_2D, texID));
    GL_CALL (glUniform1i (location, unitID));
    return true;
}


bool Program::SetUniformTextureCube (const char * uniformName, unsigned int texID, unsigned int unitID) const
{
    int location = GetUniformIndex (uniformName);
    if (location < 0)
        return false;

    GL_CALL (glActiveTexture (GL_TEXTURE0 + unitID));
    GL_CALL (glBindTexture (GL_TEXTURE_CUBE_MAP, texID));
    GL_CALL (glUniform1i (location, unitID));
    return true;
}


int Program::GetAttributeIndex (const char * attribName) const
{
    int location = -1;
    if (!m_linked)
        return location;

    GL_CALL (location = glGetAttribLocation (m_id, attribName));
    return location;
}


int Program::GetUniformIndex (const char * uniformName) const
{
    int location = -1;
    if (!m_linked)
        return location;

    GL_CALL (location = glGetUniformLocation (m_id, uniformName));
    return location;
}


unsigned int Program::LoadShaderFromFile (unsigned int type, const char * fileName) const
{
    unsigned int shaderID;
    GL_CALL (shaderID = glCreateShader (type));
    if (shaderID == 0) {
        LOG (std::string ("Error occurred during the shader creation from \'") + std::string (fileName) + std::string ("\'"));
        return 0;
    }
    std::string content;
    std::ifstream ifs {fileName};
    if (ifs && !ifs.bad ()) {
        content = std::string {std::istreambuf_iterator<char> {ifs}, std::istreambuf_iterator<char> {}};
        ifs.close ();
    } else {
        LOG (std::string ("Error occurred during the opening of \'") + std::string (fileName) + std::string ("\'"));
        GL_CALL (glDeleteShader (shaderID));
        return 0;
    }
    const char * contentCStr = content.c_str ();
    GL_CALL (glShaderSource (shaderID, 1, &contentCStr, nullptr));
    GL_CALL (glCompileShader (shaderID));
    int OK = 0;
    GL_CALL (glGetShaderiv (shaderID, GL_COMPILE_STATUS, &OK));
    if (OK == 0) {
        LOG (std::string ("Error occurred during the compilation of \'") + std::string (fileName) + std::string ("\'"));
        GetShaderErrorInfo (shaderID);
        GL_CALL (glDeleteShader (shaderID));
        return 0;
    }
    return shaderID;
}


unsigned int Program::LoadShaderFromString (unsigned int type, const char * content) const
{
    unsigned int shaderID;
    GL_CALL (shaderID = glCreateShader (type));
    if (shaderID == 0) {
        LOG (std::string ("Error occurred during the shader creation from \'") + std::string (content) + std::string ("\'"));
        return 0;
    }
    GL_CALL (glShaderSource (shaderID, 1, &content, nullptr));
    GL_CALL (glCompileShader (shaderID));
    int OK;
    GL_CALL (glGetShaderiv (shaderID, GL_COMPILE_STATUS, &OK));
    if (OK == 0) {
        LOG (std::string ("Error occurred during the compilation of \'") + std::string (content) + std::string ("\'"));
        GetShaderErrorInfo (shaderID);
        GL_CALL (glDeleteShader (shaderID));
        return 0;
    }
    return shaderID;
}

}   // namespace GLngin
