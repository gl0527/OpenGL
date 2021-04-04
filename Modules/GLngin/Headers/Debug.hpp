#pragma once

#ifndef GLNGIN_DEBUG_HPP
#define GLNGIN_DEBUG_HPP

#include "API.hpp"
#include <iostream>
#include <string>
#include <optional>

#ifdef __linux__
#include <signal.h>
#endif

#ifdef __GNUC__
#define FUNCTION __PRETTY_FUNCTION__
#define DBBREAK raise(SIGTRAP)
#elif defined _MSC_VER
#define FUNCTION __func__
#define DBBREAK __debugbreak()
#endif

#define FOLDER GLngin::GetFolderName(__FILE__)

#define LOG(msg) std::cerr << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl

#define TOSTR_HELPER(x) (#x)
#define TOSTR(x) (TOSTR_HELPER(x))

#define ASSERT(b) \
    if (!(b)) DBBREAK

#ifndef NDEBUG
#define GL_CALL(glExpr)                                                                    \
    do {                                                                                   \
        while (glGetError() != GL_NO_ERROR)                                                \
            ;                                                                              \
        glExpr;                                                                            \
        while (unsigned int error = glGetError()) {                                        \
            LOG("Error occurred during \'" #glExpr "\'")                                   \
                << "Error string: \'" << gluErrorString(error) << "\'"                     \
                << "\nError enum: \'" << GLngin::GetGLEnumStr(error) << "\'" << std::endl; \
            DBBREAK;                                                                       \
        }                                                                                  \
    } while (0)

#define IL_CALL(ilExpr)                                                                  \
    do {                                                                                 \
        while (ilGetError() != IL_NO_ERROR)                                              \
            ;                                                                            \
        ilExpr;                                                                          \
        while (unsigned int error = ilGetError()) {                                      \
            LOG("Error occurred during \'" #ilExpr "\'")                                 \
                << "Error enum: \'" << GLngin::GetILEnumStr(error) << "\'" << std::endl; \
            DBBREAK;                                                                     \
        }                                                                                \
    } while (0)

#define DEBUG_SHOW(x) (LOG(TOSTR(x) << " = " << (x)))
#else
#define GL_CALL(glExpr) glExpr
#define IL_CALL(ilExpr) ilExpr
#define DEBUG_SHOW(x)
#endif

namespace GLngin {
GLNGIN_API std::string GetGLInfoString();
GLNGIN_API const char *GetGLEnumStr(unsigned int enumElem);
GLNGIN_API const char *GetILEnumStr(unsigned int enumElem);
GLNGIN_API std::string GetFolderName(const std::string &filePath);
GLNGIN_API std::optional<std::string> GetFileContent(const std::string &filePath);
}  // namespace GLngin

#endif  // #ifndef GLNGIN_DEBUG_HPP
