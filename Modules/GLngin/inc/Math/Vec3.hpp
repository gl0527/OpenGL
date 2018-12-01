#pragma once

#ifndef GLNGIN_MATH_VEC3_HPP
#define GLNGIN_MATH_VEC3_HPP

#include "API.hpp"


namespace GLngin {
namespace Math {

class GLNGIN_API Vec3 final {
public:
                        Vec3 (float x0, float y0, float z0);
    explicit            Vec3 (float f = 0.0f);
                        Vec3 (float (&vec)[3]);

    Vec3&               operator+ ();
    Vec3                operator+ (const Vec3& vec) const;
    Vec3&               operator+= (const Vec3& vec);

    Vec3                operator- () const;
    Vec3                operator- (const Vec3& vec) const;
    Vec3&               operator-= (const Vec3& vec);

    Vec3&               operator*= (float scalar);
    Vec3                operator* (float scalar) const;

    Vec3&               operator/= (float scalar);
    Vec3                operator/ (float scalar) const;

    bool                operator== (const Vec3& vec) const;
    bool                operator!= (const Vec3& vec) const;

    float               Dot (const Vec3& vec) const;
    Vec3                Hadamard (const Vec3& vec) const;
    Vec3                Cross (const Vec3& vec) const;

    float               Length () const;
    Vec3                Normalize () const;

    static const Vec3&  Zero ();
    static const Vec3&  One ();
    static const Vec3&  UnitX ();
    static const Vec3&  UnitY ();
    static const Vec3&  UnitZ ();
    static const Vec3&  NegativeUnitX ();
    static const Vec3&  NegativeUnitY ();
    static const Vec3&  NegativeUnitZ ();

public:
    float x;
    float y;
    float z;
};

}   // namespace Math
}   // namespace GLngin

#endif  // #ifndef GLNGIN_MATH_VEC3_HPP
