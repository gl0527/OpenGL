#pragma once

#ifndef GLNGIN_MATH_MATH_HPP
#define GLNGIN_MATH_MATH_HPP

#include "API.hpp"


namespace GLngin {
namespace Math {

GLNGIN_API bool     IsEqual (float f1, float f2);
GLNGIN_API bool     IsEqual (double d1, double d2);

GLNGIN_API float    Max (float f1, float f2);
GLNGIN_API float    Min (float f1, float f2);
GLNGIN_API double   Max (double d1, double d2);
GLNGIN_API double   Min (double d1, double d2);

GLNGIN_API float    UniformRandomVariable (float a, float b);

}   // namespace Math
}   // namespace GLngin

#endif  // #ifndef GLNGIN_MATH_MATH_HPP
