#include "Sphere.hpp"

#include "Math.hpp"

namespace GLngin {

Sphere::Sphere(const Math::Vec3 &_center, float _radius)
    : center(_center)
    , radius(_radius)
{
}

VertexData Sphere::GenVertexData(float u, float v)
{
    VertexData vertexData;

    float U = u * 2 * M_PI;
    float V = v * M_PI;

    vertexData.norm = Math::Vec3(cosf(U) * sinf(V), sinf(U) * sinf(V), cos(V));
    vertexData.pos = vertexData.norm * radius + center;
    vertexData.uv = {u, v};

    return vertexData;
}

}  // namespace GLngin
