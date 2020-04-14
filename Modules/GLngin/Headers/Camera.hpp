#pragma once

#ifndef GLNGIN_CAMERA_HPP
#define GLNGIN_CAMERA_HPP

#include "API.hpp"
#include "Vec3.hpp"

namespace GLngin {
namespace Math {
class Mat4;
}  // namespace Math

class InputManager;

class GLNGIN_API Camera {
public:
    Camera(const Math::Vec3 &eye, const Math::Vec3 &lookat, const Math::Vec3 &up, int windowWidth, int windowHeight);

    Math::Mat4 View() const;
    Math::Mat4 Proj() const;

    void SetAspectRatio(int newWidth, int newHeight);

    void SetMoveSpeed(float newMoveSpeed);
    void SetTurnSpeed(float newTurnSpeed);
    void SetZoomSpeed(float newZoomSpeed);

    void Control(float t, float dt, const InputManager &input);

    const Math::Vec3 &GetPosition() const;

private:
    void CalcLocalAxes(Math::Vec3 *outLocalX, Math::Vec3 *outLocalY, Math::Vec3 *outLocalZ) const;

private:
    Math::Vec3 eye;
    Math::Vec3 lookat;
    Math::Vec3 up;

    float fov;
    float asp;
    float fp;
    float bp;

    float moveSpeed;
    float turnSpeed;
    float zoomSpeed;
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_CAMERA_HPP
