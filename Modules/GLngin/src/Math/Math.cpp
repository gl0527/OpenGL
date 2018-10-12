#include "Math.hpp"

#include <cmath>


namespace GLngin {
namespace Math {

bool IsEqual (float f1, float f2)
{
    return fabsf (f1 - f2) < 1e-4f;
}


bool IsEqual (double d1, double d2)
{
    return fabs (d1 - d2) < 1e-4;
}


float Max (float f1, float f2)
{
    return f1 > f2 ? f1 : f2;
}


float Min (float f1, float f2)
{
    return f1 < f2 ? f1 : f2;
}


double Max (double d1, double d2)
{
    return d1 > d2 ? d1 : d2;
}


double Min (double d1, double d2)
{
    return d1 < d2 ? d1 : d2;
}


float Random (float a, float b)
{
    const float min = Min (a, b);
    const float max = Max (a, b);

    return (max - min) * static_cast<float> (rand ()) / RAND_MAX + min;
}


int Random (int a, int b)
{
    return rand () % (b - a + 1) + a;
}

}   // namespace Math
}   // namespace GLngin
