#pragma once

#ifndef GLNGIN_LIGHT_HPP
#define GLNGIN_LIGHT_HPP

#include "API.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"


namespace GLngin {

struct GLNGIN_API Light {
    Math::Vec3 color;
    Math::Vec4 position;
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_LIGHT_HPP
