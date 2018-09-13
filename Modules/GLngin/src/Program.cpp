#include "Program.hpp"

#include "Mat4.hpp"
#include "Shader.hpp"
#include "Utils.hpp"
#include "Vec4.hpp"


namespace GLngin {

Program::Program (	const std::shared_ptr<Shader>& vertShader,
					const std::shared_ptr<Shader>& geomShader,
					const std::shared_ptr<Shader>& fragShader,
					const std::shared_ptr<Shader>& compShader)
{
    GL_CALL (m_handle = glCreateProgram ());
    if (m_handle == 0) {
		LOG ("Error in shader program creation.");
		exit (1);
	}
	
	AddShader (vertShader);
	AddShader (geomShader);
	AddShader (fragShader);
	AddShader (compShader);
	
	// Connect the fragmentColor to the frame buffer memory
	//glBindFragDataLocation (handle, 0, fragmentOutputVarName);
	
	// program packaging
    GL_CALL (glLinkProgram (m_handle));
	GLint OK;
    GL_CALL (glGetProgramiv (m_handle, GL_LINK_STATUS, &OK));
	if (OK == 0) {
		LOG ("Failed to link shader program!");
        GetErrorInfo (m_handle);
	}
}


Program::~Program ()
{
    for (auto it = m_shaders.begin (); it != m_shaders.end (); ++it)
        GL_CALL (glDetachShader (m_handle, it->second->GetHandle ()));

    GL_CALL (glDeleteProgram (m_handle));
}


void Program::Bind () const
{
    GL_CALL (glUseProgram (m_handle));
}


void Program::UnBind () const
{
    GL_CALL (glUseProgram (0));
}


bool Program::SetMat4 (const char * uniformName, const Mat4& value) const
{
    int location = -1;
    GL_CALL (location = glGetUniformLocation (m_handle, uniformName));
    if (location < 0)
        return false;
    GL_CALL (glUniformMatrix4fv (location, 1, GL_TRUE, value));
    return true;
}


bool Program::SetVec4 (const char * uniformName, const Vec4& value) const
{
    int location = -1;
    GL_CALL (location = glGetUniformLocation (m_handle, uniformName));
    if (location < 0)
        return false;
    GL_CALL (glUniform4fv (location, 4, value));
    return true;
}


void Program::AddShader (const std::shared_ptr<Shader>& shader)
{
	if (shader != nullptr) {
        GL_CALL (glAttachShader (m_handle, shader->GetHandle ()));
        m_shaders[shader->GetType ()] = shader;
	}
}

}	// namespace GLngine
