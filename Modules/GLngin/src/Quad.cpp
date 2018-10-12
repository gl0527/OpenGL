#include "Quad.hpp"

#include "Debug.hpp"


namespace GLngin {

Quad::Quad () :
    m_vertexArray (0),
    m_vertexBuffer (0),
    m_texCoordBuffer (0),
    m_inited (false)
{
}


Quad::~Quad ()
{
    if (!m_inited)
        return;

    GL_CALL (glDeleteBuffers (1, &m_texCoordBuffer));
    GL_CALL (glDeleteBuffers (1, &m_vertexBuffer));
    GL_CALL (glDeleteVertexArrays (1, &m_vertexArray));
}


void Quad::Init ()
{
    GL_CALL (glGenVertexArrays (1, &m_vertexArray));
    GL_CALL (glBindVertexArray (m_vertexArray));

    constexpr float vertices[] = {    // the values are in screen coordinates
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };
    GL_CALL (glGenBuffers (1, &m_vertexBuffer));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, m_vertexBuffer));
    GL_CALL (glBufferData (GL_ARRAY_BUFFER, sizeof (float) * 18, vertices, GL_STATIC_DRAW));
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
    GL_CALL (glGenBuffers (1, &m_texCoordBuffer));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, m_texCoordBuffer));
    GL_CALL (glBufferData (GL_ARRAY_BUFFER, sizeof (float) * 12, texCoords, GL_STATIC_DRAW));
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
    GL_CALL (glBindVertexArray (m_vertexArray));
    GL_CALL (glDrawArrays (GL_TRIANGLES, 0, 6));
    GL_CALL (glBindVertexArray (0));
}

}   // namespace GLngin
