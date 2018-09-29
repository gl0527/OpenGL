#include "Shader.hpp"

#include <fstream>

#include "Debug.hpp"


namespace GLngin {

Shader::Shader (unsigned int t) :
    m_handle (0),
    m_type (t),
    m_inited (false)
{
}


Shader::~Shader ()
{
    if (!m_inited)
        return;

    GL_CALL (glDeleteShader (m_handle));
}


void Shader::Init (const char * fileName)
{
    GL_CALL (m_handle = glCreateShader (m_type));
    if (m_handle == 0) {
        LOG ("Error occurred during shader creation.");
        exit (1);
    }
    std::string content;
    std::ifstream ifs {fileName};
    if (ifs && !ifs.bad ()) {
        content = std::string {std::istreambuf_iterator<char> {ifs}, std::istreambuf_iterator<char> {}};
        ifs.close ();
    } else {
        LOG ("Error occurred during shader file opening.");
        exit (1);
    }
    const char * contentCStr = content.c_str ();
    GL_CALL (glShaderSource (m_handle, 1, &contentCStr, nullptr));
    GL_CALL (glCompileShader (m_handle));
    GLint OK;
    GL_CALL (glGetShaderiv (m_handle, GL_COMPILE_STATUS, &OK));
    if (OK == 0) {
        LOG ("Error in compiling shader.");
        GetShaderErrorInfo (m_handle);
        exit (-1);
    }

    m_inited = true;
}


unsigned int Shader::GetHandle () const
{
    return m_handle;
}


unsigned int Shader::GetType () const
{
    return m_type;
}

}	// namespace GLngine
