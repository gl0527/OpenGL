#include "Cube.hpp"

#include "Debug.hpp"
#include <GL/glew.h>


namespace GLngin {

Cube::Cube () :
    m_vertexArrayID (0),
    m_vertexBufferID (0),
    m_inited (false)
{
}


Cube::~Cube ()
{
    if (!m_inited)
        return;

    GL_CALL (glDeleteBuffers (1, &m_vertexBufferID));
    GL_CALL (glDeleteVertexArrays (1, &m_vertexArrayID));
}


void Cube::Init ()
{
    GL_CALL (glGenVertexArrays (1, &m_vertexArrayID));
    GL_CALL (glBindVertexArray (m_vertexArrayID));

    constexpr float coords[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    GL_CALL (glGenBuffers (1, &m_vertexBufferID));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, m_vertexBufferID));
    GL_CALL (glBufferData (GL_ARRAY_BUFFER, sizeof (coords), coords, GL_STATIC_DRAW));
    GL_CALL (glEnableVertexAttribArray (0));
    GL_CALL (glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

    GL_CALL (glBindVertexArray (0));

    m_inited = true;
}


void Cube::Render ()
{
    if (!m_inited)
        return;

    GL_CALL (glBindVertexArray (m_vertexArrayID));
    GL_CALL (glDrawArrays (GL_TRIANGLES, 0, 36));
    GL_CALL (glBindVertexArray (0));
}

}   // namespace GLngin
