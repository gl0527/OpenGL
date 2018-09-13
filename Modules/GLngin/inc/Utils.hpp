#pragma once 

#ifndef UTILS_HPP
#define UTILS_HPP

#include "API.hpp"
#include <string>
#include <GL/glew.h>


#ifdef __GNUC__
#define FUNCTION __PRETTY_FUNCTION__
#elif defined _MSC_VER
#define FUNCTION __func__
#endif

#define LOG(msg) printf ("%s(%d, %s): %s\n",  __FILE__, __LINE__, FUNCTION, msg)

#define ASSERT(b) if (!(b)) LOG (#b "is false")

#ifndef NDEBUG
#define GL_CALL(glExpr)\
    do {                                    \
        glExpr;                             \
        unsigned int error = glGetError (); \
        if (error != GL_NO_ERROR) {         \
            LOG (#glExpr);                  \
            LOG (gluErrorString (error));   \
            exit (-1);                      \
        }                                   \
	} while (0)
#else
#define GL_CALL(glExpr) glExpr
#endif


namespace GLngin {
    template<typename T, const size_t N>
    constexpr size_t ArraySize (T (&)[N]) {
        return N;
    }

    GLNGIN_API void GetErrorInfo (unsigned int handle);
    GLNGIN_API std::string GetGLInfoString ();
}   // namespace GLngine

#endif	// #ifndef UTILS_HPP
