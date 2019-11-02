#pragma once

#ifndef GLNGIN_MATH_VEC3_HPP
#define GLNGIN_MATH_VEC3_HPP

#include "API.hpp"
#include <cmath>
#include "Math.hpp"
#include "Vec2.hpp"


namespace GLngin {
namespace Math {

class GLNGIN_API Vec3 final {
public:
    constexpr                   Vec3 (float x0, float y0, float z0);
    constexpr explicit          Vec3 (float f = 0.0f);
    constexpr                   Vec3 (const float (&vec)[3]);
    constexpr                   Vec3 (const Vec2& vec2, float z0);
    constexpr                   Vec3 (float x0, const Vec2& vec2);

    constexpr Vec2              xy () const;
    constexpr Vec2              yz () const;
    
    constexpr Vec3&             operator+ ();
    constexpr Vec3              operator+ (const Vec3& vec) const;
    constexpr Vec3&             operator+= (const Vec3& vec);
    constexpr Vec3              operator- () const;
    constexpr Vec3              operator- (const Vec3& vec) const;
    constexpr Vec3&             operator-= (const Vec3& vec);
    constexpr Vec3&             operator*= (float scalar);
    constexpr Vec3              operator* (float scalar) const;
    constexpr Vec3&             operator/= (float scalar);
    constexpr Vec3              operator/ (float scalar) const;
    inline bool                 operator== (const Vec3& vec) const;
    inline bool                 operator!= (const Vec3& vec) const;
    
    constexpr float             Dot (const Vec3& vec) const;
    constexpr Vec3              Hadamard (const Vec3& vec) const;
    constexpr Vec3              Cross (const Vec3& vec) const;
    
    inline float                Length () const;
    constexpr float             LengthSqr () const;
    inline Vec3                 Normalize () const;
    inline bool                 IsNull () const;

    inline static const Vec3&   Zero ();
    inline static const Vec3&   One ();
    inline static const Vec3&   UnitX ();
    inline static const Vec3&   UnitY ();
    inline static const Vec3&   UnitZ ();
    inline static const Vec3&   NegativeUnitX ();
    inline static const Vec3&   NegativeUnitY ();
    inline static const Vec3&   NegativeUnitZ ();

public:
    float x;
    float y;
    float z;
};


constexpr Vec3::Vec3 (float x0, float y0, float z0) :
    x (x0),
    y (y0),
    z (z0)
{
}


constexpr Vec3::Vec3 (float f /*= 0.0f*/) :
    x (f),
    y (f),
    z (f)
{
}


constexpr Vec3::Vec3 (const float (&vec)[3]) :
    x (vec[0]),
    y (vec[1]),
    z (vec[2])
{
}


constexpr Vec3::Vec3 (const Vec2& vec2, float z0) :
    x (vec2.x),
    y (vec2.y),
    z (z0)
{
}


constexpr Vec3::Vec3 (float x0, const Vec2& vec2) :
    x (x0),
    y (vec2.x),
    z (vec2.y)
{
}


constexpr Vec2 Vec3::xy () const
{
    return Vec2 (x, y);
}


constexpr Vec2 Vec3::yz () const
{
    return Vec2 (y, z);
}


constexpr Vec3& Vec3::operator+ ()
{
    return *this;
}


constexpr Vec3 Vec3::operator+ (const Vec3& vec) const
{
    return Vec3 (x + vec.x, y + vec.y, z + vec.z);
}


constexpr Vec3& Vec3::operator+= (const Vec3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}


constexpr Vec3 Vec3::operator- () const
{
    return Vec3 (-x, -y, -z);
}


constexpr Vec3 Vec3::operator- (const Vec3& vec) const
{
    return Vec3 (x - vec.x, y - vec.y, z - vec.z);
}


constexpr Vec3& Vec3::operator-= (const Vec3& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}


constexpr Vec3& Vec3::operator*= (float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}


constexpr Vec3 Vec3::operator* (float scalar) const
{
    return Vec3 (x * scalar, y * scalar, z * scalar);
}


constexpr Vec3& Vec3::operator/= (float scalar)
{
    float scalarInv = 1 / scalar;
    x *= scalarInv;
    y *= scalarInv;
    z *= scalarInv;
    return *this;
}


constexpr Vec3 Vec3::operator/ (float scalar) const
{
    float scalarInv = 1 / scalar;
    return Vec3 (x * scalarInv, y * scalarInv, z * scalarInv);
}


inline bool Vec3::operator== (const Vec3& vec) const
{
    return IsEqual (x, vec.x) && IsEqual (y, vec.y) && IsEqual (z, vec.z);
}


inline bool Vec3::operator!= (const Vec3& vec) const
{
    return !IsEqual (x, vec.x) || !IsEqual (y, vec.y) || !IsEqual (z, vec.z);
}


constexpr float Vec3::Dot (const Vec3& vec) const
{
    return x * vec.x + y * vec.y + z * vec.z;
}


constexpr Vec3 Vec3::Hadamard (const Vec3& vec) const
{
    return Vec3 (x * vec.x, y * vec.y, z * vec.z);
}


constexpr Vec3 Vec3::Cross (const Vec3& vec) const
{
    return Vec3 (y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}


inline float Vec3::Length () const
{
    return sqrtf (x * x + y * y + z * z);
}


constexpr float Vec3::LengthSqr () const
{
    return x * x + y * y + z * z;
}


inline Vec3 Vec3::Normalize () const
{
    return *this * (1 / (Length () + 1e-8f));
}


inline bool Vec3::IsNull () const
{
    return IsEqual (Length (), 0.0f);
}


inline const Vec3& Vec3::Zero ()
{
    static Vec3 Zero;

    return Zero;
}


inline const Vec3& Vec3::One ()
{
    static Vec3 One (1.0f);

    return One;
}


inline const Vec3& Vec3::UnitX ()
{
    static Vec3 UnitX (1.0f, 0.0f, 0.0f);

    return UnitX;
}


inline const Vec3& Vec3::UnitY ()
{
    static Vec3 UnitY (0.0f, 1.0f, 0.0f);

    return UnitY;
}


inline const Vec3& Vec3::UnitZ ()
{
    static Vec3 UnitZ (0.0f, 0.0f, 1.0f);

    return UnitZ;
}


inline const Vec3& Vec3::NegativeUnitX ()
{
    static Vec3 NegativeUnitX (-1.0f, 0.0f, 0.0f);

    return NegativeUnitX;
}


inline const Vec3& Vec3::NegativeUnitY ()
{
    static Vec3 NegativeUnitY (0.0f, -1.0f, 0.0f);

    return NegativeUnitY;
}


inline const Vec3& Vec3::NegativeUnitZ ()
{
    static Vec3 NegativeUnitZ (0.0f, 0.0f, -1.0f);

    return NegativeUnitZ;
}


constexpr Vec3 operator* (float scalar, const Vec3& vec)
{
    return vec * scalar;
}

}   // namespace Math
}   // namespace GLngin

#endif  // #ifndef GLNGIN_MATH_VEC3_HPP
