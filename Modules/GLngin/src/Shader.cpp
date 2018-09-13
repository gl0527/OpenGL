#include "Shader.hpp"
#include "Utils.hpp"
#include <string>
#include <fstream>


namespace GLngin {

std::string     Shader::shaderPaths[MaxPathCount] = {};
unsigned char   Shader::shaderPathCount = 0;


Shader::Shader (const char * fileName, unsigned int t) :
    m_type (t)
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
        GetErrorInfo (m_handle);
		exit (1);
	}
}


Shader::~Shader ()
{
    GL_CALL (glDeleteShader (m_handle));
}


unsigned int Shader::GetHandle () const
{
    return m_handle;
}


unsigned int Shader::GetType () const
{
    return m_type;
}


bool Shader::AddPath (const std::string& path)
{
    if (shaderPathCount < MaxPathCount) {
        shaderPaths[shaderPathCount++] = path;

        return true;
    }

    return false;
}


bool Shader::ResolveShaderPath (const char * shaderFileName)
{
    for (const std::string& s : shaderPaths) {
        std::string concat = s + std::string ("/") + std::string (shaderFileName);
        std::ifstream f (concat);
        if (f.good ())
            return true;
    }

    return false;
}

}	// namespace GLngine
