#pragma once

#ifndef GLNGIN_PARAMSURFACE_HPP
#define GLNGIN_PARAMSURFACE_HPP

#include "API.hpp"
#include "Geometry.hpp"
#include "Vec2.hpp"
#include "Vec3.hpp"

namespace GLngin {

struct VertexData {
    Math::Vec3 pos, norm;
    Math::Vec2 uv;
};

class GLNGIN_API ParamSurface : public Geometry {
public:
    virtual ~ParamSurface();

    virtual VertexData GenVertexData(float u, float v) = 0;
    void Create(int sizeX, int sizeY);
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_PARAMSURFACE_HPP
