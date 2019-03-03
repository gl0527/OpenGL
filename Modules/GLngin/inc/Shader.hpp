#pragma once

#ifndef GLNGIN_SHADER_HPP
#define GLNGIN_SHADER_HPP

#include "API.hpp"
#include <string>


namespace GLngin {

class GLNGIN_API Shader final {
public:
    explicit        Shader (unsigned int type);
                    ~Shader ();

    void            LoadFromFile (const char * fileName);
    void            LoadFromFile (const std::string & fileName);
    void            LoadFromString (const char * source);
    void            LoadFromString (const std::string & source);

    unsigned int    GetID () const;
    unsigned int    GetType () const;

private:
    unsigned int        m_id;
    const unsigned int  m_type;
    bool                m_inited;
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_SHADER_HPP
