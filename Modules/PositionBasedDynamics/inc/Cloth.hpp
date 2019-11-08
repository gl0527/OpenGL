#pragma once

#ifndef CLOTH_HPP
#define CLOTH_HPP

#include "GameObject.hpp"
#include "Program.hpp"


class Cloth : public GLngin::GameObject {
public:
    Cloth (const std::string& id, const GLngin::Math::Vec3& _position = GLngin::Math::Vec3::Zero ());

private:
    virtual void InitImpl () override;
    virtual void DrawImpl (const GLngin::RenderState& renderState) override;
    virtual void TerminateImpl () override;

private:
    GLngin::Program gravityProgram;
    GLngin::Program collisionProgram;
    GLngin::Program distanceProgram;
    GLngin::Program bendingProgram;
    GLngin::Program finalUpdateProgram;
    GLngin::Program renderProgram;

    unsigned int positionBuffer;
    unsigned int positionBufferTmp;
    unsigned int velocityBuffer;
    unsigned int vao;
    
    const unsigned int particleCountOnOneSide;
    const unsigned int vertexCount;
    const unsigned int workGroupCount;
};

#endif  // #ifndef CLOTH_HPP
