#pragma once

#ifndef GLNGIN_MATH_VEC2_HPP
#define GLNGIN_MATH_VEC2_HPP

#include "API.hpp"
#include <cmath>
#include "Math.hpp"


namespace GLngin {
namespace Math {

class GLNGIN_API Vec2 final {
public:
    constexpr                   Vec2 (float x0, float y0);
    constexpr explicit          Vec2 (float f = 0.0f);
    constexpr                   Vec2 (const float (&vec)[2]);
    
    constexpr Vec2&             operator+ ();
    constexpr Vec2              operator+ (const Vec2& vec) const;
    constexpr Vec2&             operator+= (const Vec2& vec);
    constexpr Vec2              operator- () const;
    constexpr Vec2              operator- (const Vec2& vec) const;
    constexpr Vec2&             operator-= (const Vec2& vec);
    constexpr Vec2&             operator*= (float scalar);
    constexpr Vec2              operator* (float scalar) const;
    constexpr Vec2&             operator/= (float scalar);
    constexpr Vec2              operator/ (float scalar) const;
    inline bool                 operator== (const Vec2& vec) const;
    inline bool                 operator!= (const Vec2& vec) const;
    
    constexpr float             Dot (const Vec2& vec) const;
    constexpr Vec2              Hadamard (const Vec2& vec) const;
    
    inline float                Length () const;
    constexpr float             LengthSqr () const;
    inline Vec2                 Normalize () const;
    inline bool                 IsNull () const;

    inline static const Vec2&   Zero ();
    inline static const Vec2&   One ();
    inline static const Vec2&   UnitX ();
    inline static const Vec2&   UnitY ();
    inline static const Vec2&   NegativeUnitX ();
    inline static const Vec2&   NegativeUnitY ();

public:
    float x, y;
};


constexpr Vec2::Vec2 (float x0, float y0) :
    x (x0),
    y (y0)
{
}


constexpr Vec2::Vec2 (float f /*= 0.0f*/) :
    x (f),
    y (f)
{
}


constexpr Vec2::Vec2 (const float (&vec)[2]) :
    x (vec[0]),
    y (vec[1])
{
}


constexpr Vec2& Vec2::operator+ ()
{
    return *this;
}


constexpr Vec2 Vec2::operator+ (const Vec2& vec) const
{
    return Vec2 (x + vec.x, y + vec.y);
}


constexpr Vec2& Vec2::operator+= (const Vec2& vec)
{
    x += vec.x;
    y += vec.y;
    return *this;
}


constexpr Vec2 Vec2::operator- () const
{
    return Vec2 (-x, -y);
}


constexpr Vec2 Vec2::operator- (const Vec2& vec) const
{
    return Vec2 (x - vec.x, y - vec.y);
}


constexpr Vec2& Vec2::operator-= (const Vec2& vec)
{
    x -= vec.x;
    y -= vec.y;
    return *this;
}


constexpr Vec2& Vec2::operator*= (float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}


constexpr Vec2 Vec2::operator* (float scalar) const
{
    return Vec2 (x * scalar, y * scalar);
}


constexpr Vec2& Vec2::operator/= (float scalar)
{
    float scalarInv = 1 / scalar;
    x *= scalarInv;
    y *= scalarInv;
    return *this;
}


constexpr Vec2 Vec2::operator/ (float scalar) const
{
    float scalarInv = 1 / scalar;
    return Vec2 (x * scalarInv, y * scalarInv);
}


inline bool Vec2::operator== (const Vec2& vec) const
{
    return IsEqual (x, vec.x) && IsEqual (y, vec.y);
}


inline bool Vec2::operator!= (const Vec2& vec) const
{
    return !IsEqual (x, vec.x) || !IsEqual (y, vec.y);
}


constexpr float Vec2::Dot (const Vec2& vec) const
{
    return x * vec.x + y * vec.y;
}


constexpr Vec2 Vec2::Hadamard (const Vec2& vec) const
{
    return Vec2 (x * vec.x, y * vec.y);
}


inline float Vec2::Length () const
{
    return sqrtf (x * x + y * y);
}


constexpr float Vec2::LengthSqr () const
{
    return x * x + y * y;
}


inline Vec2 Vec2::Normalize () const
{
    return *this * (1 / (Length () + 1e-8f));
}


inline bool Vec2::IsNull () const
{
    return IsEqual (Length (), 0.0f);
}


inline const Vec2& Vec2::Zero ()
{
    static Vec2 Zero;

    return Zero;
}


inline const Vec2& Vec2::One ()
{
    static Vec2 One (1.0f);

    return One;
}


inline const Vec2& Vec2::UnitX ()
{
    static Vec2 UnitX (1.0f, 0.0f);

    return UnitX;
}


inline const Vec2& Vec2::UnitY ()
{
    static Vec2 UnitY (0.0f, 1.0f);

    return UnitY;
}


inline const Vec2& Vec2::NegativeUnitX ()
{
    static Vec2 NegativeUnitX (-1.0f, 0.0f);

    return NegativeUnitX;
}


inline const Vec2& Vec2::NegativeUnitY ()
{
    static Vec2 NegativeUnitY (0.0f, -1.0f);

    return NegativeUnitY;
}

}   // namespace Math
}   // namespace GLngin

#endif  // #ifndef GLNGIN_MATH_VEC2_HPP
