#pragma once

#ifndef GLNGIN_CAMERA_HPP
#define GLNGIN_CAMERA_HPP

#include "API.hpp"
#include "Vec3.hpp"


namespace GLngin {
namespace Math {
    class Mat4;
}   // namespace Math

class InputManager;

class GLNGIN_API Camera {
public:
                Camera (const Math::Vec3& eye, const Math::Vec3& lookat, const Math::Vec3& up);

    Math::Mat4  View ();
    Math::Mat4  Proj ();

    void        Animate (float dt);

private:
    void CalcLocalAxes ();

private:
    Math::Vec3 eye;
    Math::Vec3 lookat;
    Math::Vec3 up;

    Math::Vec3 localX;
    Math::Vec3 localY;
    Math::Vec3 localZ;

    float fov;
    float asp;
    float fp;
    float bp;

    InputManager& input;
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_CAMERA_HPP
