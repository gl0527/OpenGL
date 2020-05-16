#pragma once

#ifndef GLNGIN_RENDER_STATE_HPP
#define GLNGIN_RENDER_STATE_HPP

#include "API.hpp"
#include "Light.hpp"
#include "Vec3.hpp"
#include "Mat4.hpp"
#include <vector>

namespace GLngin {

struct GLNGIN_API PerObjectData {
    Math::Mat4 M, Minv, MVP;
};

struct GLNGIN_API PerFrameData {
    Math::Mat4 V, P, VP;
    Math::Vec3 wEye;
    std::vector<Light> lights;
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_RENDER_STATE_HPP
