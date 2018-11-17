#include "Shader.hpp"

#include <fstream>

#include "Debug.hpp"


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
        std::cerr << "Shader log:\n" << log << std::endl;
        delete[] log;
    }
}

}   // namespace

Shader::Shader (unsigned int t) :
    m_id (0),
    m_type (t),
    m_inited (false)
{
}


Shader::~Shader ()
{
    if (!m_inited)
        return;

    GL_CALL (glDeleteShader (m_id));
}


void Shader::Init (const char * fileName)
{
    GL_CALL (m_id = glCreateShader (m_type));
    if (m_id == 0) {
        LOG (std::string ("Error occurred during the shader creation from \'") + std::string (fileName) + std::string ("\'"));
        exit (1);
    }
    std::string content;
    std::ifstream ifs {fileName};
    if (ifs && !ifs.bad ()) {
        content = std::string {std::istreambuf_iterator<char> {ifs}, std::istreambuf_iterator<char> {}};
        ifs.close ();
    } else {
        LOG (std::string ("Error occurred during the opening of \'") + std::string (fileName) + std::string ("\'"));
        exit (1);
    }
    const char * contentCStr = content.c_str ();
    GL_CALL (glShaderSource (m_id, 1, &contentCStr, nullptr));
    GL_CALL (glCompileShader (m_id));
    int OK;
    GL_CALL (glGetShaderiv (m_id, GL_COMPILE_STATUS, &OK));
    if (OK == 0) {
        LOG (std::string ("Error occurred during the compilation of \'") + std::string (fileName) + std::string ("\'"));
        GetShaderErrorInfo (m_id);
        exit (-1);
    }

    m_inited = true;
}


unsigned int Shader::GetID () const
{
    return m_id;
}


unsigned int Shader::GetType () const
{
    return m_type;
}

}	// namespace GLngine
