#pragma once

#ifndef GLNGIN_MATH_MATH_HPP
#define GLNGIN_MATH_MATH_HPP

#include "API.hpp"
#include <cmath>


namespace GLngin {
namespace Math {

inline constexpr float Pi = 3.14159265f;


constexpr float AngleToRadian (float angle)
{
    return angle * Pi / 180;
}


constexpr float RadianToAngle (float radian)
{
    return radian * 180 / Pi;
}


inline bool IsEqual (float f1, float f2)
{
    return fabsf (f1 - f2) < 1e-4f;
}


inline bool IsEqual (double d1, double d2)
{
    return fabs (d1 - d2) < 1e-4;
}


constexpr float Max (float f1, float f2)
{
    return f1 > f2 ? f1 : f2;
}


constexpr float Min (float f1, float f2)
{
    return f1 < f2 ? f1 : f2;
}


constexpr double Max (double d1, double d2)
{
    return d1 > d2 ? d1 : d2;
}


constexpr double Min (double d1, double d2)
{
    return d1 < d2 ? d1 : d2;
}


inline float Random (float a, float b)
{
    const float min = Min (a, b);
    const float max = Max (a, b);

    return (max - min) * static_cast<float> (rand ()) / RAND_MAX + min;
}


inline int Random (int a, int b)
{
    return rand () % (b - a + 1) + a;
}

}   // namespace Math
}   // namespace GLngin

#endif  // #ifndef GLNGIN_MATH_MATH_HPP
