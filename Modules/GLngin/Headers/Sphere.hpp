#pragma once

#ifndef GLNGIN_SPHERE_HPP
#define GLNGIN_SPHERE_HPP

#include "API.hpp"
#include "ParamSurface.hpp"
#include "Vec3.hpp"

namespace GLngin {

class GLNGIN_API Sphere : public ParamSurface {
public:
    Sphere(const Math::Vec3 &_center, float _radius);

    virtual VertexData GenVertexData(float u, float v) override;

private:
    Math::Vec3 center;
    float radius;
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_SPHERE_HPP
