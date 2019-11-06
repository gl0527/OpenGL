#include "Cloth.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cstdio>
#include <cstring>

#include "Debug.hpp"
#include "Vec4.hpp"
#include "Camera.hpp"
#include "Mat4.hpp"
#include "RenderState.hpp"


Cloth::Cloth (const std::string& id, const GLngin::Math::Vec3& _position /*= GLngin::Math::Vec3::Zero ()*/) :
    GameObject (id, _position),
    particleCountOnOneSide (64),
    vertexCount (particleCountOnOneSide * particleCountOnOneSide),
    workGroupCount (32)
{
}


void Cloth::InitImpl ()
{
    // Set point primitive size
    GL_CALL (glPointSize (4.0f));
    GL_CALL (glEnable (GL_POINT_SMOOTH));

    GL_CALL (glEnable (GL_BLEND));
    GL_CALL (glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::string currFolder (FOLDER);

    // initialize programs
    gravityProgram.Init ();
    gravityProgram.AddShaderFromFile (GL_COMPUTE_SHADER, currFolder + "../shaders/gravity.comp");
    gravityProgram.Link ();

    collisionProgram.Init ();
    collisionProgram.AddShaderFromFile (GL_COMPUTE_SHADER, currFolder + "../shaders/collision.comp");
    collisionProgram.Link ();

    distanceProgram.Init ();
    distanceProgram.AddShaderFromFile (GL_COMPUTE_SHADER, currFolder + "../shaders/distance.comp");
    distanceProgram.Link ();

    bendingProgram.Init ();
    bendingProgram.AddShaderFromFile (GL_COMPUTE_SHADER, currFolder + "../shaders/bending.comp");
    bendingProgram.Link ();

    finalUpdateProgram.Init ();
    finalUpdateProgram.AddShaderFromFile (GL_COMPUTE_SHADER, currFolder + "../shaders/finalUpdate.comp");
    finalUpdateProgram.Link ();

    renderProgram.Init ();
    renderProgram.AddShaderFromFile (GL_VERTEX_SHADER, currFolder + "../shaders/render.vert");
    renderProgram.AddShaderFromFile (GL_FRAGMENT_SHADER, currFolder + "../shaders/render.frag");
    renderProgram.Link ();

    // set up constant uniform variables
    const float dt = 0.0015f;

    gravityProgram.Use ();
    gravityProgram.SetUniformFloat ("dt", dt);

    collisionProgram.Use ();
    collisionProgram.SetUniformFloat ("ConstraintWeight", 0.9f);

    distanceProgram.Use ();
    distanceProgram.SetUniformFloat ("ConstraintWeight", 0.25f);

    finalUpdateProgram.Use ();
    finalUpdateProgram.SetUniformFloat ("dt", dt);

    // Initialize the particle position buffer
    GL_CALL (glGenBuffers (1, &positionBuffer));
    GL_CALL (glBindBuffer (GL_SHADER_STORAGE_BUFFER, positionBuffer));
    GL_CALL (glBufferData (GL_SHADER_STORAGE_BUFFER, vertexCount * sizeof (GLngin::Math::Vec4), nullptr, GL_STATIC_DRAW));

    GLngin::Math::Vec4 * pos = nullptr;
    GL_CALL (pos = static_cast<GLngin::Math::Vec4*> (glMapBufferRange (GL_SHADER_STORAGE_BUFFER,
                                                                      0,
                                                                      vertexCount * sizeof (GLngin::Math::Vec4),
                                                                      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)));
    for (unsigned int i = 0; i < particleCountOnOneSide; ++i)
        for (unsigned int j = 0; j < particleCountOnOneSide; ++j)
        {
            pos[i*particleCountOnOneSide+j] =
                GLngin::Math::Vec4 (i / (particleCountOnOneSide - 1.0f) - 0.5f, 0.5f, j / (particleCountOnOneSide - 1.0f) - 0.5f, 1.0f);
        }
    GL_CALL (glUnmapBuffer (GL_SHADER_STORAGE_BUFFER));

    GL_CALL (glGenBuffers (1, &positionBufferTmp));
    GL_CALL (glBindBuffer (GL_SHADER_STORAGE_BUFFER, positionBufferTmp));
    GL_CALL (glBufferData (GL_SHADER_STORAGE_BUFFER, vertexCount * sizeof (GLngin::Math::Vec4), nullptr, GL_STATIC_DRAW));

    GL_CALL (glMapBufferRange (GL_SHADER_STORAGE_BUFFER,
                              0,
                              vertexCount * sizeof (GLngin::Math::Vec4),
                              GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
    GL_CALL (glUnmapBuffer (GL_SHADER_STORAGE_BUFFER));

    GL_CALL (glGenBuffers (1, &velocityBuffer));
    GL_CALL (glBindBuffer (GL_SHADER_STORAGE_BUFFER, velocityBuffer));
    GL_CALL (glBufferData (GL_SHADER_STORAGE_BUFFER, vertexCount * sizeof (GLngin::Math::Vec4), nullptr, GL_STATIC_DRAW));

    GLngin::Math::Vec4 * vel = nullptr;
    GL_CALL (vel = static_cast<GLngin::Math::Vec4*> (glMapBufferRange (GL_SHADER_STORAGE_BUFFER, 0, vertexCount * sizeof (GLngin::Math::Vec4), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)));
    for (unsigned int i = 0; i < vertexCount; ++i) {
        vel[i] = GLngin::Math::Vec4 ();
    }
    GL_CALL (glUnmapBuffer (GL_SHADER_STORAGE_BUFFER));

    GL_CALL (glBindBuffer (GL_SHADER_STORAGE_BUFFER, 0));

    // Initialize the vertex array object with the position buffer
    GL_CALL (glGenVertexArrays (1, &vao));
    GL_CALL (glBindVertexArray (vao));

    int vPositionIndex = renderProgram.GetAttributeIndex ("vPosition");
    GL_CALL (glEnableVertexAttribArray (vPositionIndex));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, positionBuffer));
    GL_CALL (glVertexAttribPointer (vPositionIndex, 4, GL_FLOAT, GL_FALSE, sizeof (GLngin::Math::Vec4), nullptr));

    GL_CALL (glBindVertexArray (0));
}


void Cloth::DrawImpl (const GLngin::RenderState& renderState) const
{
    GL_CALL (glBindBufferBase (GL_SHADER_STORAGE_BUFFER, 0, positionBuffer));
    GL_CALL (glBindBufferBase (GL_SHADER_STORAGE_BUFFER, 1, positionBufferTmp));
    GL_CALL (glBindBufferBase (GL_SHADER_STORAGE_BUFFER, 2, velocityBuffer));

    gravityProgram.Use ();
    const unsigned int workgroupsize = particleCountOnOneSide / workGroupCount;
    GL_CALL (glDispatchCompute (workgroupsize, workgroupsize, 1));
    GL_CALL (glMemoryBarrier (GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));

    for (int i = 0; i < 50; ++i) {
        collisionProgram.Use ();
        GL_CALL (glDispatchCompute (workgroupsize, workgroupsize, 1));
        GL_CALL (glMemoryBarrier (GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));

        distanceProgram.Use ();
        GL_CALL (glDispatchCompute (workgroupsize, workgroupsize, 1));
        GL_CALL (glMemoryBarrier (GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));
    }

    finalUpdateProgram.Use ();
    GL_CALL (glDispatchCompute (workgroupsize, workgroupsize, 1));
    GL_CALL (glMemoryBarrier (GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));

    // Render the particles
    renderProgram.Use ();
    renderProgram.SetUniformMat4 ("MVP", GLngin::Math::Mat4::Translate (GLngin::Math::Vec3 (0,1,0)) * renderState.viewProj.value ());
    GL_CALL (glBindVertexArray (vao));
    GL_CALL (glDrawArrays (GL_POINTS, 0, vertexCount));
    GL_CALL (glBindVertexArray (0));
    renderProgram.UnUse ();
}


void Cloth::TerminateImpl ()
{
    renderProgram.UnUse ();
    finalUpdateProgram.UnUse ();
    bendingProgram.UnUse ();
    distanceProgram.UnUse ();
    collisionProgram.UnUse ();
    gravityProgram.UnUse ();

    GL_CALL (glDeleteBuffers (1, &velocityBuffer));
    GL_CALL (glDeleteBuffers (1, &positionBufferTmp));
    GL_CALL (glDeleteBuffers (1, &positionBuffer));
    GL_CALL (glDeleteVertexArrays (1, &vao));
}
