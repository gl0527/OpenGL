#include "Camera.hpp"

#include <cmath>

#include "Mat4.hpp"
#include "Math.hpp"
#include "Vec4.hpp"
#include "InputManager.hpp"


namespace GLngin {

Camera::Camera (const Math::Vec3& eye, const Math::Vec3& lookat, const Math::Vec3& up) :
    eye (eye),
    lookat (lookat),
    up (up),
    fov (Math::AngleToRadian (60)),
    asp (1.0f),
    fp (0.5f),
    bp (1000.0f),
    moveSpeed (3.0f),
    turnSpeed (2.0f),
    input (InputManager::Instance ())
{
}


Math::Mat4 Camera::View () const
{
    Math::Vec3 localX, localY, localZ;
    CalcLocalAxes (&localX, &localY, &localZ);

    return Math::Mat4::Translate (-eye) * Math::Mat4 (  localX.x, localY.x, localZ.x, 0.0f,
                                                        localX.y, localY.y, localZ.y, 0.0f,
                                                        localX.z, localY.z, localZ.z, 0.0f,
                                                        0.0f, 0.0f, 0.0f, 1.0f);
}


Math::Mat4 Camera::Proj () const
{
    float yScale = 1 / tanf (fov * 0.5f);
    float xScale = yScale / asp;

    return Math::Mat4 ( xScale, 0.0f,   0.0f,             0.0f,
                        0.0f,   yScale, 0.0f,             0.0f,
                        0.0f,   0.0f,   (fp+bp)/(fp-bp),  -1.0f,
                        0.0f,   0.0f,   2*fp*bp/(fp-bp),  0.0f);
}


void Camera::SetMoveSpeed (float newMoveSpeed)
{
    moveSpeed = newMoveSpeed;
}


void Camera::SetTurnSpeed (float newTurnSpeed)
{
    turnSpeed = newTurnSpeed;
}


void Camera::Animate (float dt)
{
    Math::Vec3 localX, localY, localZ;
    CalcLocalAxes (&localX, &localY, &localZ);
    
    Math::Vec3 acc;

    if (input.IsKeyDown (InputManager::Key::w)) {
        acc -= localZ;
    }
    if (input.IsKeyDown (InputManager::Key::s)) {
        acc += localZ;
    }
    if (input.IsKeyDown (InputManager::Key::d)) {
        acc += localX;
    }
    if (input.IsKeyDown (InputManager::Key::a)) {
        acc -= localX;
    }
    if (input.IsKeyDown (InputManager::Key::q)) {
        acc += localY;
    }
    if (input.IsKeyDown (InputManager::Key::e)) {
        acc -= localY;
    }

    Math::Vec3 dAcc = acc.Normalize () * dt * moveSpeed;
    eye += dAcc;
    lookat += dAcc;

    int dx, dy;
    input.GetMouseDelta (&dx, &dy);

    Math::Vec3 dir = (lookat - eye).Normalize ();
    Math::Mat4 rotAroundX = Math::Mat4::Identity ();
    if (dir.Dot (Math::Vec3::UnitY ()) > -0.8f && dir.Dot (Math::Vec3::UnitY ()) < 0.8f)
        rotAroundX = Math::Mat4::Rotate (dt * dy * turnSpeed, localX);
    Math::Mat4 rotAroundY = Math::Mat4::Rotate (-dt * dx * turnSpeed, localY);

    lookat = (Math::Vec4 (lookat, 1.0f) * Math::Mat4::Translate (-eye) * rotAroundX * rotAroundY * Math::Mat4::Translate (eye)).xyz ();
}


void Camera::CalcLocalAxes (Math::Vec3* outLocalX, Math::Vec3* outLocalY, Math::Vec3* outLocalZ) const
{
    *outLocalZ = (eye - lookat).Normalize ();
    *outLocalX = up.Cross (*outLocalZ).Normalize ();
    *outLocalY = outLocalZ->Cross (*outLocalX);
}

}   // namespace GLngin
