#pragma once

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "GameObject.hpp"
#include "Shader.hpp"
#include "Cube.hpp"

class Background : public GLngin::GameObject {
public:
    Background( const std::string &id,
                const std::string &right,
                const std::string &left,
                const std::string &top,
                const std::string &bottom,
                const std::string &front,
                const std::string &back);

private:
    virtual void InitImpl() override;
    virtual void DrawImpl(const GLngin::RenderState &renderState) override;

private:
    GLngin::Shader program;
    GLngin::Cube cube;
    std::string names[6];
};

#endif  // #ifndef BACKGROUND_HPP
