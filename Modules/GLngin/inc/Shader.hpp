#pragma once

#ifndef SHADER_HPP
#define SHADER_HPP

#include "API.hpp"
#include <string>


namespace GLngin {

class GLNGIN_API Shader final {
public:
                    Shader (const char * fileName, unsigned int t);
                    ~Shader ();
	
    unsigned int    GetHandle () const;
    unsigned int    GetType () const;

    static bool     AddPath (const std::string& path);

private:
    unsigned int                    m_handle;
    const unsigned int              m_type;

    static constexpr unsigned char  MaxPathCount = 8;
    static std::string              shaderPaths[MaxPathCount];
    static unsigned char            shaderPathCount;

    static bool     ResolveShaderPath (const char * shaderFileName);
};

}	// namespace GLngine

#endif	// #ifndef SHADER_HPP
