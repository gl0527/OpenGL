#include "Debug.hpp"

#include <cmath>


namespace GLngin {

void GetShaderErrorInfo (unsigned int handle)
{
    int logLen;
	GL_CALL (glGetShaderiv (handle, GL_INFO_LOG_LENGTH, &logLen));
	if (logLen > 0) {
		char * log = new char[logLen];
        int written;
        GL_CALL (glGetShaderInfoLog (handle, logLen, &written, &log[0]));   // TODO glGetProgramInfoLog kene a program eseten!!!
        std::cerr << "Shader log:\n" << log << std::endl;
		delete[] log;
	}
}


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


std::string GetGLInfoString ()
{
    int majorVersion, minorVersion;
    char buf[256];
    constexpr char FormatString[] = "GL Vendor            : %s\n"
                                    "GL Renderer          : %s\n"
                                    "GL Version (string)  : %s\n"
                                    "GL Version (integer) : %d.%d\n"
                                    "GLSL Version         : %s\n";

    GL_CALL (glGetIntegerv (GL_MAJOR_VERSION, &majorVersion));
    GL_CALL (glGetIntegerv (GL_MINOR_VERSION, &minorVersion));

    GL_CALL (sprintf (buf, FormatString, glGetString (GL_VENDOR), glGetString (GL_RENDERER),
                      glGetString (GL_VERSION), majorVersion, minorVersion, glGetString (GL_SHADING_LANGUAGE_VERSION)));

    return buf;
}

}   // namespace GLngin
