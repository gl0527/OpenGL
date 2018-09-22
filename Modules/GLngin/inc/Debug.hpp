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

#ifndef NDEBUG
#define GL_CALL(glExpr)                                     \
    do {                                                    \
        glExpr;                                             \
        unsigned int error = glGetError ();                 \
        if (error != GL_NO_ERROR) {                         \
            LOG ("Error occurred during \'" #glExpr "\'")   \
            << "Error string: \'" << gluErrorString (error) \
            << "\'" << std::endl;                           \
            DBBREAK;                                        \
            exit (-1);                                      \
        }                                                   \
	} while (0)
#else
#define GL_CALL(glExpr) glExpr
#endif


namespace GLngin {
    GLNGIN_API void         GetErrorInfo (unsigned int handle);
    GLNGIN_API std::string  GetGLInfoString ();
}   // namespace GLngine

#endif	// #ifndef GLNGIN_DEBUG_HPP
