#pragma once

#ifndef GLNGIN_QUAD_HPP
#define GLNGIN_QUAD_HPP

#include "API.hpp"


namespace GLngin {

class GLNGIN_API Quad final {
public:
            Quad ();
            ~Quad ();

    void    Init ();
    void    Render ();
    void    Render (int width, int height);

private:
    unsigned int    m_vertexArray;
    unsigned int    m_vertexBuffer;
    unsigned int    m_texCoordBuffer;
    bool            m_inited;
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_QUAD_HPP
