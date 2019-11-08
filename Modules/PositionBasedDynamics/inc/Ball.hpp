#pragma once

#ifndef BALL_HPP
#define BALL_HPP

#include "GameObject.hpp"
#include "Program.hpp"


class Ball : public GLngin::GameObject {
public:
    using GameObject::GameObject;

private:
    virtual void InitImpl () override;
    virtual void DrawImpl (const GLngin::RenderState& renderState) override;

private:
    GLngin::Program program;
};

#endif  // #ifndef BALL_HPP