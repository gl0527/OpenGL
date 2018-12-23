#pragma once

#ifndef GLNGIN_CUBE_HPP
#define GLNGIN_CUBE_HPP

#include "API.hpp"


namespace GLngin {

class GLNGIN_API Cube final {
public:
            Cube ();
            ~Cube ();

    void    Init ();
    void    Render ();

private:
    unsigned int    m_vertexArrayID;
    unsigned int    m_vertexBufferID;
    bool            m_inited;
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_CUBE_HPP
