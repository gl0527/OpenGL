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
    localZ ((eye - lookat).Normalize ()),
    localX (up.Cross (localZ).Normalize ()),
    localY (localZ.Cross (localX)),
    fov (Math::AngleToRadian (60)),
    asp (1.0f),
    fp (0.5f),
    bp (1000.0f),
    input (InputManager::Instance ())
{
}


Math::Mat4 Camera::View ()
{
    CalcLocalAxes ();

    return Math::Mat4::Translate (-eye) * Math::Mat4 (  localX.x, localY.x, localZ.x, 0.0f,
                                                        localX.y, localY.y, localZ.y, 0.0f,
                                                        localX.z, localY.z, localZ.z, 0.0f,
                                                        0.0f, 0.0f, 0.0f, 1.0f);
}


Math::Mat4 Camera::Proj ()
{
    float yScale = 1 / tanf (fov * 0.5f);
    float xScale = yScale / asp;

    return Math::Mat4 ( xScale, 0.0f,   0.0f,             0.0f,
                        0.0f,   yScale, 0.0f,             0.0f,
                        0.0f,   0.0f,   (fp+bp)/(fp-bp),  -1.0f,
                        0.0f,   0.0f,   2*fp*bp/(fp-bp),  0.0f);
}


void Camera::Animate (float dt)
{
    CalcLocalAxes ();
    
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

    Math::Vec3 dAcc = acc.Normalize () * dt;
    eye += dAcc;
    lookat += dAcc;

    int dx, dy;
    InputManager::Instance ().GetMouseDelta (&dx, &dy);

    lookat = (Math::Vec4 (lookat, 1.0f) * Math::Mat4::Translate (-eye) * Math::Mat4::Rotate (dt * dy, localX) * Math::Mat4::Rotate (-dt * dx, localY) * Math::Mat4::Translate (eye)).xyz ();
}


void Camera::CalcLocalAxes ()
{
    localZ = (eye - lookat).Normalize ();
    localX = up.Cross (localZ).Normalize ();
    localY = localZ.Cross (localX);
}

}   // namespace GLngin
