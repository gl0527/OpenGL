#include "ParamSurface.hpp"

#include "Debug.hpp"

#include <GL/glew.h>
#include <vector>


namespace GLngin {

ParamSurface::~ParamSurface ()
{
}


void ParamSurface::Create (int sizeX, int sizeY)
{
    numOfVertices = sizeX * sizeY * 6;
    
    unsigned int vbo;
    GL_CALL (glGenBuffers (1, &vbo));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, vbo));

    std::vector<VertexData> vertexData;

    for (int i = 0; i < sizeX; ++i) {
        for (int j = 0; j < sizeY; ++j) {
            // triangle 1
            vertexData.push_back (GenVertexData ((float)i/sizeX, (float)j/sizeY));
            vertexData.push_back (GenVertexData ((float)(i+1)/sizeX, (float)j/sizeY));
            vertexData.push_back (GenVertexData ((float)i/sizeX, (float)(j+1)/sizeY));
            
            // triangle 2
            vertexData.push_back (GenVertexData ((float)(i+1)/sizeX, (float)j/sizeY));
            vertexData.push_back (GenVertexData ((float)(i+1)/sizeX, (float)(j+1)/sizeY));
            vertexData.push_back (GenVertexData ((float)i/sizeX, (float)(j+1)/sizeY));
        }
    }

    GL_CALL (glBufferData (GL_ARRAY_BUFFER, numOfVertices * sizeof (VertexData), &vertexData[0], GL_STATIC_DRAW));

    GL_CALL (glEnableVertexAttribArray (0));
    GL_CALL (glEnableVertexAttribArray (1));
    GL_CALL (glEnableVertexAttribArray (2));

    GL_CALL (glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof (VertexData), (void*) offsetof (VertexData, pos)));
    GL_CALL (glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof (VertexData), (void*) offsetof (VertexData, norm)));
    GL_CALL (glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof (VertexData), (void*) offsetof (VertexData, uv)));
}

}   // namespace GLngin
