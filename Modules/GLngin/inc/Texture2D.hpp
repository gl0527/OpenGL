#pragma once

#ifndef GLNGIN_TEXTURE_2D_HPP
#define GLNGIN_TEXTURE_2D_HPP

#include "API.hpp"


namespace GLngin {

class GLNGIN_API Texture2D final {
public:
                    Texture2D (int width, int height);
                    ~Texture2D ();

    void            Init ();

    unsigned int    GetHandle () const;
    int             GetWidth () const;
    int             GetHeight () const;

    void            SetData (float * data);
	
private:
    unsigned int    m_handle;
    const int       m_width;
    const int       m_height;
    bool            m_inited;
};

}	// namespace GLngin

#endif	// #ifndef GLNGIN_TEXTURE_2D_HPP
