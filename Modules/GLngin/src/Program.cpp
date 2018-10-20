#include "Program.hpp"

#include "Debug.hpp"
#include "Mat4.hpp"
#include "Shader.hpp"
#include "Vec4.hpp"


namespace GLngin {

namespace {

void GetProgramErrorInfo (unsigned int handle)
{
    int logLen;
    GL_CALL (glGetProgramiv (handle, GL_INFO_LOG_LENGTH, &logLen));
    if (logLen > 0) {
        char * log = new char[logLen];
        int written;
        GL_CALL (glGetProgramInfoLog (handle, logLen, &written, &log[0]));
        std::cerr << "Program log:\n" << log << std::endl;
        delete[] log;
    }
}

}   // namepace

Program::Program () :
    m_handle (0),
    m_inited (false),
    m_linked (false)
{
}


Program::~Program ()
{
    if (!m_inited)
        return;

    for (auto& s : m_shaders)
        GL_CALL (glDetachShader (m_handle, s.GetHandle ()));

    m_shaders.clear ();

    GL_CALL (glDeleteProgram (m_handle));
}


void Program::Init ()
{
    GL_CALL (m_handle = glCreateProgram ());
    if (m_handle == 0)
        LOG ("Error in shader program creation.");

    m_inited = true;
}


void Program::AddShader (const Shader& shader)
{
    m_shaders.push_back (shader);
    GL_CALL (glAttachShader (m_handle, m_shaders[m_shaders.size () - 1].GetHandle ()));
}


void Program::Link ()
{
    if (!m_inited)
        return;

    GL_CALL (glLinkProgram (m_handle));
    int OK = 0;
    GL_CALL (glGetProgramiv (m_handle, GL_LINK_STATUS, &OK));
    if (OK == 0) {
        LOG ("Failed to link shader program!");
        GetProgramErrorInfo (m_handle);
        exit (-1);
    }
    m_linked = true;
}


void Program::Enable () const
{
    if (!m_linked)
        return;

    GL_CALL (glUseProgram (m_handle));
}


void Program::Disable () const
{
    GL_CALL (glUseProgram (0));
}


unsigned int Program::GetHandle () const
{
    return m_handle;
}


bool Program::SetUniformMat4 (const char * uniformName, const Math::Mat4& value) const
{
    if (!m_inited)
        return false;

    int location = -1;
    GL_CALL (location = glGetUniformLocation (m_handle, uniformName));
    if (location < 0)
        return false;
    GL_CALL (glUniformMatrix4fv (location, 1, GL_TRUE, value));
    return true;
}


bool Program::SetUniformVec4 (const char * uniformName, const Math::Vec4& value) const
{
    if (!m_inited)
        return false;

    int location = -1;
    GL_CALL (location = glGetUniformLocation (m_handle, uniformName));
    if (location < 0)
        return false;
    GL_CALL (glUniform4f (location, value.x, value.y, value.z, value.w));
    return true;
}

}	// namespace GLngine
