#pragma once

#ifndef GLNGIN_MATH_VEC4_HPP
#define GLNGIN_MATH_VEC4_HPP

#include "API.hpp"


namespace GLngin {
namespace Math {

class Mat4;
class Vec3;

class GLNGIN_API Vec4 final {
public:
                        Vec4 (float x0, float y0, float z0, float w0);
    explicit            Vec4 (float f = 0.0f);
                        Vec4 (float (&vec)[4]);
                        Vec4 (const Vec3& vec3, float w0);
                        Vec4 (float x0, const Vec3& vec3);

    Vec3                xyz () const;
    Vec3                yzw () const;

    Vec4&               operator+ ();
    Vec4                operator+ (const Vec4& vec) const;
    Vec4&               operator+= (const Vec4& vec);

    Vec4                operator- ();
    Vec4                operator- (const Vec4& vec) const;
    Vec4&               operator-= (const Vec4& vec);

    Vec4&               operator*= (float scalar);
    Vec4                operator* (float scalar) const;
    Vec4                operator* (const Mat4& mat) const;

    Vec4&               operator/= (float scalar);
    Vec4                operator/ (float scalar) const;

    bool                operator== (const Vec4& vec) const;
    bool                operator!= (const Vec4& vec) const;

    float               Dot (const Vec4& vec) const;
    Vec4                Hadamard (const Vec4& vec) const;

    static const Vec4&  Zero ();
    static const Vec4&  One ();
    static const Vec4&  UnitX ();
    static const Vec4&  UnitY ();
    static const Vec4&  UnitZ ();
    static const Vec4&  UnitW ();
    static const Vec4&  NegativeUnitX ();
    static const Vec4&  NegativeUnitY ();
    static const Vec4&  NegativeUnitZ ();
    static const Vec4&  NegativeUnitW ();

public:
    float x;
    float y;
    float z;
    float w;
};

}   // namespace Math
}	// namespace GLngine

#endif	// #ifndef GLNGIN_MATH_VEC4_HPP
