#pragma once

#ifndef GLNGIN_SHADER_HPP
#define GLNGIN_SHADER_HPP

#include "API.hpp"


namespace GLngin {

class GLNGIN_API Shader final {
public:
    explicit        Shader (unsigned int t);
                    ~Shader ();
	
    void            Init (const char * fileName);

    unsigned int    GetHandle () const;
    unsigned int    GetType () const;

private:
    unsigned int        m_handle;
    const unsigned int  m_type;
    bool                m_inited;
};

}	// namespace GLngine

#endif	// #ifndef GLNGIN_SHADER_HPP
