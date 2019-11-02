#pragma once

#ifndef GLNGIN_MATH_MATH_HPP
#define GLNGIN_MATH_MATH_HPP

#include <cmath>


namespace GLngin {
namespace Math {

inline constexpr float M_PI_180 = 0.01745329251994329576922f;
inline constexpr float M_180_PI = 57.29577951308232087685f;
inline constexpr float M_1_LOG2 = 3.32192809488736234787f;

constexpr float DegToRad (float deg)
{
    return deg * M_PI_180;
}


constexpr float RadToDeg (float rad)
{
    return rad * M_180_PI;
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


inline double Log2 (double d)
{
    return log (d) * M_1_LOG2;
}

}   // namespace Math
}   // namespace GLngin

#endif  // #ifndef GLNGIN_MATH_MATH_HPP
