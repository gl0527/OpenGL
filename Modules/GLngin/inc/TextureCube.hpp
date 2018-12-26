#pragma once

#ifndef GLNGIN_TEXTURE_CUBE_HPP
#define GLNGIN_TEXTURE_CUBE_HPP

#include "API.hpp"
#include <string>


namespace GLngin {

class GLNGIN_API TextureCube final {
public:
                    TextureCube ();
                    ~TextureCube ();

    void            Init ();
    bool            Load (const char * right, const char * left, const char * top, const char * bottom, const char * front, const char * back);
    bool            Load (const std::string& right, const std::string& left, const std::string& top, const std::string& bottom, const std::string& front, const std::string& back);
    bool            Load (const char* (&arr)[6]);

    unsigned int    GetID () const;

private:
    unsigned int    m_id;
    bool            m_inited;
};

}	// namespace GLngin

#endif	// #ifndef GLNGIN_TEXTURE_CUBE_HPP
