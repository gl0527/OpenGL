#include "Quad.hpp"

#include "Debug.hpp"

#include <GL/glew.h>


namespace GLngin {

Quad::Quad () :
    m_vertexArrayID (0),
    m_vertexBufferID (0),
    m_texCoordBufferID (0),
    m_inited (false)
{
}


Quad::~Quad ()
{
    if (!m_inited)
        return;

    GL_CALL (glDeleteBuffers (1, &m_texCoordBufferID));
    GL_CALL (glDeleteBuffers (1, &m_vertexBufferID));
    GL_CALL (glDeleteVertexArrays (1, &m_vertexArrayID));
}


void Quad::Init ()
{
    GL_CALL (glGenVertexArrays (1, &m_vertexArrayID));
    GL_CALL (glBindVertexArray (m_vertexArrayID));

    constexpr float vertices[] = {    // the values are in screen coordinates
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
         1.0f, -1.0f, 0.0f
    };
    GL_CALL (glGenBuffers (1, &m_vertexBufferID));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, m_vertexBufferID));
    GL_CALL (glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW));
    GL_CALL (glEnableVertexAttribArray (0));
    GL_CALL (glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

    constexpr float texCoords[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    GL_CALL (glGenBuffers (1, &m_texCoordBufferID));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, m_texCoordBufferID));
    GL_CALL (glBufferData (GL_ARRAY_BUFFER, sizeof (texCoords), texCoords, GL_STATIC_DRAW));
    GL_CALL (glEnableVertexAttribArray (1));
    GL_CALL (glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0, nullptr));

    GL_CALL (glBindVertexArray (0));

    m_inited = true;
}


void Quad::Render () const
{
    if (!m_inited)
        return;

    RenderImpl ();
}


void Quad::Render (int lowerLeftX, int lowerLeftY, int width, int height) const
{
    if (!m_inited)
        return;

    // save current viewport
    int viewPort[4];
    GL_CALL (glGetIntegerv (GL_VIEWPORT, viewPort));

    // modify viewport, and draw into it
    GL_CALL (glViewport (lowerLeftX, lowerLeftY, width, height));
    RenderImpl ();

    // reset viewport
    GL_CALL (glViewport (viewPort[0], viewPort[1], viewPort[2], viewPort[3]));
}


void Quad::RenderImpl () const
{
    GL_CALL (glBindVertexArray (m_vertexArrayID));
    GL_CALL (glDrawArrays (GL_TRIANGLES, 0, 6));
    GL_CALL (glBindVertexArray (0));
}

}   // namespace GLngin
