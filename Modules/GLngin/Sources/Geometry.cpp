#include "Geometry.hpp"

#include "Debug.hpp"
#include <GL/glew.h>


namespace GLngin {

Geometry::~Geometry ()
{
    GL_CALL (glDeleteVertexArrays (1, &vao));
}


void Geometry::Init ()
{
    GL_CALL (glGenVertexArrays (1, &vao));
    GL_CALL (glBindVertexArray (vao));
}


void Geometry::Draw ()
{
    GL_CALL (glBindVertexArray (vao));
    GL_CALL (glDrawArrays (GL_TRIANGLES, 0, numOfVertices));    // TODO elvileg TRIANGLE_STRIP-pel hatekonyabb lenne, de ehhez a Create-be is bele kell nyulni valszeg
    GL_CALL (glBindVertexArray (0));
}

}   // namespace GLngin
