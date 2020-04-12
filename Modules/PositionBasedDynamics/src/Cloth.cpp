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

Cloth::Cloth(const std::string &id, const GLngin::Math::Vec3 &_position /*= GLngin::Math::Vec3::Zero ()*/)
    : GameObject(id, _position)
    , particleCountOnOneSide(64)
    , vertexCount(particleCountOnOneSide * particleCountOnOneSide)
    , workGroupCount(32)
{
}

void Cloth::InitImpl()
{
    // Set point primitive size
    GL_CALL(glPointSize(4.0f));
    GL_CALL(glEnable(GL_POINT_SMOOTH));

    GL_CALL(glEnable(GL_BLEND));
    GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::string currFolder(FOLDER);

    std::string gravityCS;
    if (auto gravityCSOpt = GLngin::GetFileContent(currFolder + "../shaders/gravity.comp")) {
        gravityCS = gravityCSOpt.value();
    } else {
        // TODO error handling
    }

    std::string collisionCS;
    if (auto collisionCSOpt = GLngin::GetFileContent(currFolder + "../shaders/collision.comp")) {
        collisionCS = collisionCSOpt.value();
    } else {
        // TODO error handling
    }

    std::string distanceCS;
    if (auto distanceCSOpt = GLngin::GetFileContent(currFolder + "../shaders/distance.comp")) {
        distanceCS = distanceCSOpt.value();
    } else {
        // TODO error handling
    }

    std::string bendingCS;
    if (auto bendingCSOpt = GLngin::GetFileContent(currFolder + "../shaders/bending.comp")) {
        bendingCS = bendingCSOpt.value();
    } else {
        // TODO error handling
    }

    std::string finalUpdateCS;
    if (auto finalUpdateCSOpt = GLngin::GetFileContent(currFolder + "../shaders/finalUpdate.comp")) {
        finalUpdateCS = finalUpdateCSOpt.value();
    } else {
        // TODO error handling
    }

    std::string vs;
    if (auto vsOpt = GLngin::GetFileContent(currFolder + "../shaders/render.vert")) {
        vs = vsOpt.value();
    } else {
        // TODO error handling
    }

    std::string fs;
    if (auto fsOpt = GLngin::GetFileContent(currFolder + "../shaders/render.frag")) {
        fs = fsOpt.value();
    } else {
        // TODO error handling
    }

    // initialize programs
    gravityProgram.Init(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, gravityCS);
    collisionProgram.Init(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, collisionCS);
    distanceProgram.Init(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, distanceCS);
    bendingProgram.Init(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, bendingCS);
    finalUpdateProgram.Init(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt, finalUpdateCS);
    renderProgram.Init(vs, std::nullopt, std::nullopt, std::nullopt, fs, std::nullopt);

    // set up constant uniform variables
    const float dt = 0.0015f;

    gravityProgram.Bind();
    gravityProgram.SetUniformFloat("dt", dt);

    collisionProgram.Bind();
    collisionProgram.SetUniformFloat("ConstraintWeight", 0.9f);

    distanceProgram.Bind();
    distanceProgram.SetUniformFloat("ConstraintWeight", 0.25f);

    finalUpdateProgram.Bind();
    finalUpdateProgram.SetUniformFloat("dt", dt);

    // Initialize the particle position buffer
    GL_CALL(glGenBuffers(1, &positionBuffer));
    GL_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, positionBuffer));
    GL_CALL(glBufferData(GL_SHADER_STORAGE_BUFFER, vertexCount * sizeof(GLngin::Math::Vec4), nullptr, GL_STATIC_DRAW));

    GLngin::Math::Vec4 *pos = nullptr;
    GL_CALL(pos = static_cast<GLngin::Math::Vec4 *>(glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0,
                                                                     vertexCount * sizeof(GLngin::Math::Vec4),
                                                                     GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)));
    for (unsigned int i = 0; i < particleCountOnOneSide; ++i)
        for (unsigned int j = 0; j < particleCountOnOneSide; ++j) {
            pos[i * particleCountOnOneSide + j] = GLngin::Math::Vec4(i / (particleCountOnOneSide - 1.0f) - 0.5f, 0.5f,
                                                                     j / (particleCountOnOneSide - 1.0f) - 0.5f, 1.0f);
        }
    GL_CALL(glUnmapBuffer(GL_SHADER_STORAGE_BUFFER));

    GL_CALL(glGenBuffers(1, &positionBufferTmp));
    GL_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, positionBufferTmp));
    GL_CALL(glBufferData(GL_SHADER_STORAGE_BUFFER, vertexCount * sizeof(GLngin::Math::Vec4), nullptr, GL_STATIC_DRAW));

    GL_CALL(glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, vertexCount * sizeof(GLngin::Math::Vec4),
                             GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
    GL_CALL(glUnmapBuffer(GL_SHADER_STORAGE_BUFFER));

    GL_CALL(glGenBuffers(1, &velocityBuffer));
    GL_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, velocityBuffer));
    GL_CALL(glBufferData(GL_SHADER_STORAGE_BUFFER, vertexCount * sizeof(GLngin::Math::Vec4), nullptr, GL_STATIC_DRAW));

    GLngin::Math::Vec4 *vel = nullptr;
    GL_CALL(vel = static_cast<GLngin::Math::Vec4 *>(glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0,
                                                                     vertexCount * sizeof(GLngin::Math::Vec4),
                                                                     GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)));
    for (unsigned int i = 0; i < vertexCount; ++i) {
        vel[i] = GLngin::Math::Vec4();
    }
    GL_CALL(glUnmapBuffer(GL_SHADER_STORAGE_BUFFER));

    GL_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0));

    // Initialize the vertex array object with the position buffer
    GL_CALL(glGenVertexArrays(1, &vao));
    GL_CALL(glBindVertexArray(vao));

    int vPositionIndex = renderProgram.GetAttributeLocation("vPosition");
    GL_CALL(glEnableVertexAttribArray(vPositionIndex));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, positionBuffer));
    GL_CALL(glVertexAttribPointer(vPositionIndex, 4, GL_FLOAT, GL_FALSE, sizeof(GLngin::Math::Vec4), nullptr));

    GL_CALL(glBindVertexArray(0));
}

void Cloth::DrawImpl(const GLngin::RenderState &renderState)
{
    GL_CALL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, positionBuffer));
    GL_CALL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, positionBufferTmp));
    GL_CALL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, velocityBuffer));

    gravityProgram.Bind();
    const unsigned int workgroupsize = particleCountOnOneSide / workGroupCount;
    GL_CALL(glDispatchCompute(workgroupsize, workgroupsize, 1));
    GL_CALL(glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));

    for (int i = 0; i < 50; ++i) {
        collisionProgram.Bind();
        GL_CALL(glDispatchCompute(workgroupsize, workgroupsize, 1));
        GL_CALL(glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));

        distanceProgram.Bind();
        GL_CALL(glDispatchCompute(workgroupsize, workgroupsize, 1));
        GL_CALL(glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));
    }

    finalUpdateProgram.Bind();
    GL_CALL(glDispatchCompute(workgroupsize, workgroupsize, 1));
    GL_CALL(glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));

    // Render the particles
    renderProgram.Bind();
    renderProgram.SetUniformMat4(
        "MVP", GLngin::Math::Mat4::Translate(GLngin::Math::Vec3(0, 1, 0)) * renderState.viewProj.value());
    GL_CALL(glBindVertexArray(vao));
    GL_CALL(glDrawArrays(GL_POINTS, 0, vertexCount));
    GL_CALL(glBindVertexArray(0));
    renderProgram.UnBind();
}

void Cloth::TerminateImpl()
{
    renderProgram.UnBind();
    finalUpdateProgram.UnBind();
    bendingProgram.UnBind();
    distanceProgram.UnBind();
    collisionProgram.UnBind();
    gravityProgram.UnBind();

    GL_CALL(glDeleteBuffers(1, &velocityBuffer));
    GL_CALL(glDeleteBuffers(1, &positionBufferTmp));
    GL_CALL(glDeleteBuffers(1, &positionBuffer));
    GL_CALL(glDeleteVertexArrays(1, &vao));
}
