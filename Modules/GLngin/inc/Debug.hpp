#pragma once 

#ifndef GLNGIN_DEBUG_HPP
#define GLNGIN_DEBUG_HPP

#include "API.hpp"
#include <iostream>

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
#define GL_CALL(glExpr)                                         \
    do {                                                        \
        while (glGetError () != GL_NO_ERROR);                   \
        glExpr;                                                 \
        while (unsigned int error = glGetError ()) {            \
            LOG ("Error occurred during \'" #glExpr "\'")       \
            << "Error string: \'" << gluErrorString (error)     \
            << "\'" << "\nError enum: \'" <<                    \
            GLngin::GetGLEnumStr (error) << "\'" << std::endl;  \
            DBBREAK;                                            \
        }                                                       \
	} while (0)

#define IL_CALL(ilExpr)                                         \
    do {                                                        \
        while (ilGetError () != IL_NO_ERROR);                   \
        ilExpr;                                                 \
        while (unsigned int error = ilGetError ()) {            \
            LOG ("Error occurred during \'" #ilExpr "\'") <<    \
            "Error enum: \'" << GLngin::GetILEnumStr (error) << \
            "\'" << std::endl;                                  \
            DBBREAK;                                            \
        }                                                       \
    } while (0)
#else
#define GL_CALL(glExpr) glExpr
#define IL_CALL(ilExpr) ilExpr
#endif


namespace GLngin {
    GLNGIN_API std::string GetGLInfoString ();
    GLNGIN_API const char * GetGLEnumStr (unsigned int enumElem);
    GLNGIN_API const char * GetILEnumStr (unsigned int enumElem);
    // TODO call stack kiiratasa hiba eseten!!!
}   // namespace GLngine

#endif	// #ifndef GLNGIN_DEBUG_HPP
