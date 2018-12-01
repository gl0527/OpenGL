#pragma once

#ifndef GLNGIN_QUAD_HPP
#define GLNGIN_QUAD_HPP

#include "API.hpp"


namespace GLngin {

// TODO index buffer hasznalata, hogy ne kelljen a vertexeket duplikalni
class GLNGIN_API Quad final {
public:
            Quad ();
            ~Quad ();

    void    Init ();
    void    Render () const;
    void    Render (int lowerLeftX, int lowerLeftY, int width, int height) const;

private:
    unsigned int    m_vertexArrayID;
    unsigned int    m_vertexBufferID;
    unsigned int    m_texCoordBufferID;
    bool            m_inited;

    void    RenderImpl () const;
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_QUAD_HPP
