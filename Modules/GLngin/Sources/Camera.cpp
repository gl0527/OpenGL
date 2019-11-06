#include "Camera.hpp"

#include "Mat4.hpp"
#include "Math.hpp"
#include "Vec2.hpp"
#include "Vec4.hpp"
#include "InputManager.hpp"


namespace GLngin {

Camera::Camera (const Math::Vec3& eye, const Math::Vec3& lookat, const Math::Vec3& up, int windowWidth, int windowHeight) :
    eye (eye),
    lookat (lookat),
    up (up),
    fov (Math::DegToRad (60.0f)),
    asp (static_cast<float> (windowWidth) / windowHeight),
    fp (0.1f),
    bp (100.0f),
    moveSpeed (3.0f),
    turnSpeed (2.0f),
    zoomSpeed (30.0f)
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
    const float yScale = 1 / tanf (fov * 0.5f);

    return Math::Mat4 ( yScale/asp, 0.0f,   0.0f,             0.0f,
                        0.0f,       yScale, 0.0f,             0.0f,
                        0.0f,       0.0f,   (fp+bp)/(fp-bp),  -1.0f,
                        0.0f,       0.0f,   2*fp*bp/(fp-bp),  0.0f);
}


void Camera::SetAspectRatio (int newWidth, int newHeight)
{
    asp = static_cast<float> (newWidth) / newHeight;
}


void Camera::SetMoveSpeed (float newMoveSpeed)
{
    moveSpeed = newMoveSpeed;
}


void Camera::SetTurnSpeed (float newTurnSpeed)
{
    turnSpeed = newTurnSpeed;
}


void Camera::SetZoomSpeed (float newZoomSpeed)
{
    zoomSpeed = newZoomSpeed;
}


void Camera::Control (float /*t*/, float dt, const InputManager& input)
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
    if (input.IsScrollUp () && fov > Math::DegToRad (20.0f)) {
        fov -= zoomSpeed * dt;
    }
    if (input.IsScrollDown () && fov < Math::DegToRad (120.0f)) {
        fov += zoomSpeed * dt;
    }

    acc = acc.Normalize () * dt * moveSpeed;
    eye += acc;
    lookat += acc;

    const Math::Vec2 dMouse = input.GetMouseDelta ();
    const Math::Vec3 dir = (lookat - eye).Normalize ();
    const float dirDotY = dir.Dot (Math::Vec3::UnitY ());
    Math::Mat4 rotAroundX = Math::Mat4::Identity ();

    if ((dirDotY > -0.9f || dMouse.y > 0) && (dirDotY < 0.9f || dMouse.y < 0)) {
        rotAroundX = Math::Mat4::Rotate (dt * dMouse.y * turnSpeed, localX);
    }
    Math::Mat4 rotAroundY = Math::Mat4::Rotate (-dt * dMouse.x * turnSpeed, localY);

    lookat = (Math::Vec4 (lookat, 1.0f) * Math::Mat4::Translate (-eye) * rotAroundX * rotAroundY * Math::Mat4::Translate (eye)).xyz ();
}


void Camera::CalcLocalAxes (Math::Vec3* outLocalX, Math::Vec3* outLocalY, Math::Vec3* outLocalZ) const
{
    *outLocalZ = (eye - lookat).Normalize ();
    *outLocalX = up.Cross (*outLocalZ).Normalize ();
    *outLocalY = outLocalZ->Cross (*outLocalX);
}

}   // namespace GLngin
