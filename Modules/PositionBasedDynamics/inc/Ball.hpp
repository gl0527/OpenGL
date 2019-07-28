#pragma once

#ifndef BALL_HPP
#define BALL_HPP

#include "GameObject.hpp"


class Ball : public GLngin::GameObject {
public:
    using GameObject::GameObject;

private:
    virtual void InitImpl () override;
    virtual void DrawImpl (const GLngin::Camera* const camera) const override;
};

#endif  // #ifndef BALL_HPP
