#pragma once

#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include "GameObject.hpp"
#include "Cube.hpp"

class Background : public GLngin::GameObject {
public:
    Background(const std::string &id, const std::shared_ptr<GLngin::Material::Material> &_material,
               const std::string (&_names)[6]);

private:
    virtual void InitImpl() override;
    virtual void DrawImpl(const GLngin::PerFrameData &pfd) override;

private:
    GLngin::Cube cube;
    std::string names[6];
};

#endif  // #ifndef BACKGROUND_HPP
