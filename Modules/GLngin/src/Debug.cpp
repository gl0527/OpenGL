#include "Debug.hpp"

#include <cmath>


namespace GLngin {

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
