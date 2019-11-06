#pragma once

#ifndef GLNGIN_RENDER_STATE_HPP
#define GLNGIN_RENDER_STATE_HPP

#include "API.hpp"
#include "Light.hpp"
#include "Vec3.hpp"
#include "Mat4.hpp"
#include <optional>


namespace GLngin {

class GLNGIN_API RenderState {
public:
    std::optional<Math::Mat4> model;
    std::optional<Math::Mat4> modelInv;
    std::optional<Math::Mat4> viewProj;
    std::optional<Math::Mat4> modelViewProj;
    std::optional<Math::Vec3> cameraPos;
    std::optional<Light> light;
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_RENDER_STATE_HPP
