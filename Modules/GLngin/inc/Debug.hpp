#pragma once 

#ifndef GLNGIN_DEBUG_HPP
#define GLNGIN_DEBUG_HPP

#include "API.hpp"
#include <iostream>
#include <string>
#include <GL/glew.h>

#ifdef __linux__
#include <signal.h>
#endif


#ifdef __GNUC__
#define FUNCTION __PRETTY_FUNCTION__
#define DBBREAK raise (SIGTRAP)
#elif defined _MSC_VER
#define FUNCTION __func__
#define DBBREAK __debugbreak ()
#endif

#define LOG(msg) std::cerr << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl

#define ASSERT(b) if (!(b)) DBBREAK

#ifndef NDEBUG
#define GL_CALL(glExpr)                                     \
    do {                                                    \
        while (glGetError () != GL_NO_ERROR);               \
        glExpr;                                             \
        while (unsigned int error = glGetError ()) {        \
            LOG ("Error occurred during \'" #glExpr "\'")   \
            << "Error string: \'" << gluErrorString (error) \
            << "\'" << std::endl;                           \
            DBBREAK;                                        \
        }                                                   \
	} while (0)
#else
#define GL_CALL(glExpr) glExpr
#endif


namespace GLngin {
    GLNGIN_API void         GetShaderErrorInfo (unsigned int handle);
    GLNGIN_API void         GetProgramErrorInfo (unsigned int handle);
    GLNGIN_API std::string  GetGLInfoString ();
}   // namespace GLngine

#endif	// #ifndef GLNGIN_DEBUG_HPP
