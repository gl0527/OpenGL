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

    GL_CALL (glDeleteBuffers(1, &m_vertexBuffer));
    GL_CALL (glDeleteVertexArrays(1, &m_vertexArray));
    GL_CALL (glDeleteVertexArrays(1, &m_texCoordBuffer));
}


void Quad::Init ()
{
    GL_CALL (glGenVertexArrays(1, &m_vertexArray));
    GL_CALL (glBindVertexArray(m_vertexArray));

    float vertices[] = {    // the values are in screen coordinates
        -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f
    };
    GL_CALL (glGenBuffers(1, &m_vertexBuffer));
    GL_CALL (glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer));
    GL_CALL (glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, vertices, GL_STATIC_DRAW));
    GL_CALL (glEnableVertexAttribArray(0));
    GL_CALL (glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

    float texCoords[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        0.0f, 0.0f,
        0.0f, 0.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    GL_CALL (glGenBuffers(1, &m_texCoordBuffer));
    GL_CALL (glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer));
    GL_CALL (glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, texCoords, GL_STATIC_DRAW));
    GL_CALL (glEnableVertexAttribArray(1));
    GL_CALL (glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr));

    GL_CALL (glBindVertexArray(0));

    m_inited = true;
}


void Quad::Render ()
{
    if (!m_inited)
        return;

    GL_CALL (glBindVertexArray(m_vertexArray));
    GL_CALL (glDrawArrays(GL_TRIANGLES, 0, 6));
    GL_CALL (glBindVertexArray(0));
}


void Quad::Render (int width, int height)
{
    if (!m_inited)
        return;

    int viewPort [4];

    GL_CALL (glGetIntegerv(GL_VIEWPORT, viewPort));
    GL_CALL (glViewport(0, 0, width, height));
    GL_CALL (glBindVertexArray(m_vertexArray));
    GL_CALL (glDrawArrays(GL_TRIANGLES, 0, 6));
    GL_CALL (glBindVertexArray(0));
    GL_CALL (glViewport(viewPort[0], viewPort[1], viewPort[2], viewPort[3]));
}

}   // namespace GLngin
