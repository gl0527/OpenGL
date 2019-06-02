#pragma once

#ifndef GLNGIN_MATH_VEC4_HPP
#define GLNGIN_MATH_VEC4_HPP

#include "API.hpp"
#include "Math.hpp"
#include "Vec3.hpp"
#include "Vec2.hpp"


namespace GLngin {
namespace Math {

class Mat4;

class GLNGIN_API Vec4 final {
public:
    constexpr                   Vec4 (float x0, float y0, float z0, float w0);
    constexpr explicit          Vec4 (float f = 0.0f);
    constexpr                   Vec4 (const float (&vec)[4]);
    constexpr                   Vec4 (const Vec3& vec3, float w0);
    constexpr                   Vec4 (float x0, const Vec3& vec3);
    constexpr                   Vec4 (const Vec2& vec2, float z0, float w0);
    constexpr                   Vec4 (float x0, const Vec2& vec2, float w0);
    constexpr                   Vec4 (float x0, float y0, const Vec2& vec2);

    constexpr Vec3              xyz () const;
    constexpr Vec3              yzw () const;
    constexpr Vec2              xy () const;
    constexpr Vec2              yz () const;
    constexpr Vec2              zw () const;

    constexpr Vec4&             operator+ ();
    constexpr Vec4              operator+ (const Vec4& vec) const;
    constexpr Vec4&             operator+= (const Vec4& vec);
    constexpr Vec4              operator- ();
    constexpr Vec4              operator- (const Vec4& vec) const;
    constexpr Vec4&             operator-= (const Vec4& vec);
    constexpr Vec4&             operator*= (float scalar);
    constexpr Vec4              operator* (float scalar) const;
    Vec4                        operator* (const Mat4& mat) const;
    constexpr Vec4&             operator/= (float scalar);
    constexpr Vec4              operator/ (float scalar) const;
    inline bool                 operator== (const Vec4& vec) const;
    inline bool                 operator!= (const Vec4& vec) const;

    constexpr float             Dot (const Vec4& vec) const;
    constexpr Vec4              Hadamard (const Vec4& vec) const;

    inline float                Length () const;
    constexpr float             LengthSqr () const;
    inline Vec4                 Normalize () const;

    inline static const Vec4&   Zero ();
    inline static const Vec4&   One ();
    inline static const Vec4&   UnitX ();
    inline static const Vec4&   UnitY ();
    inline static const Vec4&   UnitZ ();
    inline static const Vec4&   UnitW ();
    inline static const Vec4&   NegativeUnitX ();
    inline static const Vec4&   NegativeUnitY ();
    inline static const Vec4&   NegativeUnitZ ();
    inline static const Vec4&   NegativeUnitW ();

public:
    float x;
    float y;
    float z;
    float w;
};


constexpr Vec4::Vec4 (float x0, float y0, float z0, float w0) :
    x (x0),
    y (y0),
    z (z0),
    w (w0)
{
}


constexpr Vec4::Vec4 (float f/*= 0.0f*/) :
    x (f),
    y (f),
    z (f),
    w (f)
{
}


constexpr Vec4::Vec4 (const float (&vec)[4]) :
    x (vec[0]),
    y (vec[1]),
    z (vec[2]),
    w (vec[3])
{
}


constexpr Vec4::Vec4 (const Vec3& vec3, float w0) :
    x (vec3.x),
    y (vec3.y),
    z (vec3.z),
    w (w0)
{
}


constexpr Vec4::Vec4 (float x0, const Vec3& vec3) :
    x (x0),
    y (vec3.x),
    z (vec3.y),
    w (vec3.z)
{
}


constexpr Vec4::Vec4 (const Vec2& vec2, float z0, float w0) :
    x (vec2.x),
    y (vec2.y),
    z (z0),
    w (w0)
{
}


constexpr Vec4::Vec4 (float x0, const Vec2& vec2, float w0) :
    x (x0),
    y (vec2.x),
    z (vec2.y),
    w (w0)
{
}


constexpr Vec4::Vec4 (float x0, float y0, const Vec2& vec2) :
    x (x0),
    y (y0),
    z (vec2.x),
    w (vec2.y)
{
}


constexpr Vec3 Vec4::xyz () const
{
    return Vec3 (x, y, z);
}


constexpr Vec3 Vec4::yzw () const
{
    return Vec3 (y, z, w);
}


constexpr Vec2 Vec4::xy () const
{
    return Vec2 (x, y);
}


constexpr Vec2 Vec4::yz () const
{
    return Vec2 (y, z);
}


constexpr Vec2 Vec4::zw () const
{
    return Vec2 (z, w);
}


constexpr Vec4& Vec4::operator+ ()
{
    return *this;
}


constexpr Vec4 Vec4::operator+ (const Vec4& vec) const
{
    return Vec4 (x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}


constexpr Vec4& Vec4::operator+= (const Vec4& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;
    return *this;
}


constexpr Vec4 Vec4::operator- ()
{
    return Vec4 (-x, -y, -z, -w);
}


constexpr Vec4 Vec4::operator- (const Vec4& vec) const
{
    return Vec4 (x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}


constexpr Vec4& Vec4::operator-= (const Vec4& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;
    return *this;
}


constexpr Vec4& Vec4::operator*= (float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}


constexpr Vec4 Vec4::operator* (float scalar) const
{
    return Vec4 (x * scalar, y * scalar, z * scalar, w * scalar);
}


constexpr Vec4& Vec4::operator/= (float scalar)
{
    float scalarInv = 1 / scalar;
    x *= scalarInv;
    y *= scalarInv;
    z *= scalarInv;
    w *= scalarInv;
    return *this;
}


constexpr Vec4 Vec4::operator/ (float scalar) const
{
    float scalarInv = 1 / scalar;
    return Vec4 (x * scalarInv, y * scalarInv, z * scalarInv, w * scalarInv);
}


inline bool Vec4::operator== (const Vec4& vec) const
{
    return  IsEqual (x, vec.x) &&
            IsEqual (y, vec.y) &&
            IsEqual (z, vec.z) &&
            IsEqual (w, vec.w);
}


inline bool Vec4::operator!= (const Vec4& vec) const
{
    return  !IsEqual (x, vec.x) ||
            !IsEqual (y, vec.y) ||
            !IsEqual (z, vec.z) ||
            !IsEqual (w, vec.w);
}


constexpr float Vec4::Dot (const Vec4& vec) const
{
    return x*vec.x + y*vec.y + z*vec.z + w*vec.w;
}


constexpr Vec4 Vec4::Hadamard (const Vec4& vec) const
{
    return Vec4 (x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}


inline float Vec4::Length () const
{
    return sqrtf (x * x + y * y + z * z + w * w);
}


constexpr float Vec4::LengthSqr () const
{
    return x * x + y * y + z * z + w * w;
}


inline Vec4 Vec4::Normalize () const
{
    return *this * (1 / (Length () + 1e-8f));
}


inline const Vec4& Vec4::Zero ()
{
    static Vec4 Zero (0.0f, 0.0f, 0.0f, 0.0f);

    return Zero;
}


inline const Vec4& Vec4::One ()
{
    static Vec4 One (1.0f, 1.0f, 1.0f, 1.0f);

    return One;
}


inline const Vec4& Vec4::UnitX ()
{
    static Vec4 UnitX (1.0f, 0.0f, 0.0f, 0.0f);

    return UnitX;
}


inline const Vec4& Vec4::UnitY ()
{
    static Vec4 UnitY (0.0f, 1.0f, 0.0f, 0.0f);

    return UnitY;
}


inline const Vec4& Vec4::UnitZ ()
{
    static Vec4 UnitZ (0.0f, 0.0f, 1.0f, 0.0f);

    return UnitZ;
}


inline const Vec4& Vec4::UnitW ()
{
    static Vec4 UnitW (0.0f, 0.0f, 0.0f, 1.0f);

    return UnitW;
}


inline const Vec4& Vec4::NegativeUnitX ()
{
    static Vec4 NegativeUnitX (-1.0f, 0.0f, 0.0f, 0.0f);

    return NegativeUnitX;
}


inline const Vec4& Vec4::NegativeUnitY ()
{
    static Vec4 NegativeUnitY (0.0f, -1.0f, 0.0f, 0.0f);

    return NegativeUnitY;
}


inline const Vec4& Vec4::NegativeUnitZ ()
{
    static Vec4 NegativeUnitZ (0.0f, 0.0f, -1.0f, 0.0f);

    return NegativeUnitZ;
}


inline const Vec4& Vec4::NegativeUnitW ()
{
    static Vec4 NegativeUnitW (0.0f, 0.0f, 0.0f, -1.0f);

    return NegativeUnitW;
}

}   // namespace Math
}   // namespace GLngin

#endif  // #ifndef GLNGIN_MATH_VEC4_HPP
