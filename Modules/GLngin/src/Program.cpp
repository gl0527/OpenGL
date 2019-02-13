#include "Program.hpp"

#include "Debug.hpp"
#include "Mat4.hpp"
#include "Shader.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

#include <GL/glew.h>


namespace GLngin {

namespace {

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

    for (auto& s : m_shaders)
        GL_CALL (glDetachShader (m_id, s.GetID ()));

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


bool Program::AddShader (const Shader& shader)
{
    if (!m_inited || m_linked)
        return false;

    m_shaders.push_back (shader);
    GL_CALL (glAttachShader (m_id, m_shaders[m_shaders.size () - 1].GetID ()));
    return true;
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

}   // namespace GLngine
