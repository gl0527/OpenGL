#include "Program.hpp"

#include "Debug.hpp"
#include "Mat4.hpp"
#include "Shader.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"


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
        std::cerr << "Program log:\n" << log << std::endl;
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


void Program::AddShader (const Shader& shader)
{
    m_shaders.push_back (shader);
    GL_CALL (glAttachShader (m_id, m_shaders[m_shaders.size () - 1].GetID ()));
}


void Program::Link ()
{
    if (!m_inited)
        return;

    GL_CALL (glLinkProgram (m_id));
    int OK = 0;
    GL_CALL (glGetProgramiv (m_id, GL_LINK_STATUS, &OK));
    if (OK == 0) {
        LOG ("Failed to link shader program!");
        GetProgramErrorInfo (m_id);
        exit (-1);
    }
    m_linked = true;
}


void Program::Enable () const
{
    if (!m_linked)
        return;

    GL_CALL (glUseProgram (m_id));
}


void Program::Disable () const
{
    GL_CALL (glUseProgram (0));
}


unsigned int Program::GetID () const
{
    return m_id;
}


bool Program::SetUniformFloat (const char * uniformName, float value) const
{    
    int location = GetLocation (uniformName);
    if (location < 0)
        return false;
    GL_CALL (glUniform1f (location, value));
    return true;
}


bool Program::SetUniformInt (const char * uniformName, int value) const
{
    int location = GetLocation (uniformName);
    if (location < 0)
        return false;
    GL_CALL (glUniform1i (location, value));
    return true;
}


bool Program::SetUniformMat4 (const char * uniformName, const Math::Mat4& value) const
{
    int location = GetLocation (uniformName);
    if (location < 0)
        return false;
    GL_CALL (glUniformMatrix4fv (location, 1, GL_TRUE, value));
    return true;
}


bool Program::SetUniformVec3 (const char * uniformName, const Math::Vec3& value) const
{
    int location = GetLocation (uniformName);
    if (location < 0)
        return false;
    GL_CALL (glUniform3f (location, value.x, value.y, value.z));
    return true;
}


bool Program::SetUniformVec4 (const char * uniformName, const Math::Vec4& value) const
{
    int location = GetLocation (uniformName);
    if (location < 0)
        return false;
    GL_CALL (glUniform4f (location, value.x, value.y, value.z, value.w));
    return true;
}


int Program::GetLocation (const char * uniformName) const
{
    int location = -1;

    if (!m_inited)
        return location;

    GL_CALL (location = glGetUniformLocation (m_id, uniformName));

    return location;
}

}	// namespace GLngine
