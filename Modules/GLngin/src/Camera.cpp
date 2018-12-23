#include "Camera.hpp"

#include <cmath>

#include "Mat4.hpp"
#include "Math.hpp"
#include "Vec4.hpp"
#include "InputManager.hpp"


namespace GLngin {

Camera::Camera (const Math::Vec3& eye, const Math::Vec3& ahead, const Math::Vec3& up) :
    m_eye (eye),
    m_ahead (ahead),
    m_up (up),
    m_yaw (0.0f),
    m_pitch (0.0f),
    m_fov (Math::AngleToRadian (90)),
    m_aspect (1.0f),
    m_front (0.5f),
    m_back (1000.0f)
{
    SetAspect (m_aspect);
    SetView (m_eye, m_ahead, m_up);
}


const Math::Vec3& Camera::GetPosition () const
{
    return m_eye;
}


const Math::Vec3& Camera::GetDirection () const
{
    return m_ahead;
}


const Math::Mat4& Camera::GetViewMatrix () const
{
    return m_viewMat;
}


const Math::Mat4& Camera::GetProjMatrix () const
{
    return m_projMat;
}


void Camera::UpdateProj ()
{
    float yScale = 1 / tanf (m_fov * 0.5f);
    float xScale = yScale / m_aspect;
    float f = m_back;
    float n = m_front;

    m_projMat = Math::Mat4 (xScale, 0.0f,   0.0f,          0.0f,
                            0.0f,   yScale, 0.0f,          0.0f,
                            0.0f,   0.0f,   (n+f)/(n-f),  -1.0f,
                            0.0f,   0.0f,   2*n*f/(n-f),   0.0f);
}


void Camera::SetView (const Math::Vec3& eye, const Math::Vec3& ahead, const Math::Vec3& up)
{
    m_eye = eye;
    m_ahead = ahead.Normalize ();
    m_yaw = atan2f (m_ahead.x, m_ahead.z);
    m_pitch = -atan2f (m_ahead.y, sqrtf (m_ahead.x * m_ahead.x + m_ahead.z * m_ahead.z));

    m_right = ahead.Cross (up).Normalize ();
    m_up = m_right.Cross (ahead).Normalize ();

    // The view matrix of the camera is its model matrix inverted
    m_viewMat = Math::Mat4 (m_right, m_up, -m_ahead, m_eye).Invert ();
}


void Camera::SetProj (float fov, float aspect, float nearPlane, float farPlane)
{
    m_fov = fov;
    m_aspect = aspect;
    m_front = nearPlane;
    m_back = farPlane;
    UpdateProj ();
}


void Camera::SetAspect (float aspect)
{
    m_aspect = aspect;
    UpdateProj ();
}


void Camera::LookAt (const Math::Vec3& target)
{
    Math::Vec3 ahead = (target - m_eye).Normalize ();
    SetView (m_eye, ahead, Math::Vec3::UnitY ());
}


void Camera::Animate (float dt)
{
    if (InputManager::Instance ().IsKeyDown (InputManager::Key::w)) {
        m_eye += m_ahead * 0.001f * dt;
    }
    if (InputManager::Instance ().IsKeyDown (InputManager::Key::s)) {
        m_eye -= m_ahead * 0.001f * dt;
    }
    if (InputManager::Instance ().IsKeyDown (InputManager::Key::d)) {
        m_eye += m_right * 0.001f * dt;
    }
    if (InputManager::Instance ().IsKeyDown (InputManager::Key::a)) {
        m_eye -= m_right * 0.001f * dt;
    }
    if (InputManager::Instance ().IsKeyDown (InputManager::Key::q)) {
        m_eye += m_up * 0.001f * dt;
    }
    if (InputManager::Instance ().IsKeyDown (InputManager::Key::e)) {
        m_eye -= m_up * 0.001f * dt;
    }

    int dx, dy;
    InputManager::Instance ().GetMouseDelta (&dx, &dy);

    m_yaw += 0.02f * dx;
    m_pitch += 0.005f * dy;

    if (m_pitch < -Math::Pi * 0.49f)
        m_pitch = -Math::Pi * 0.49f;
    else if (m_pitch > Math::Pi * 0.49f)
        m_pitch = Math::Pi * 0.49f;

    m_ahead = Math::Vec3 (sinf (m_yaw) * cosf (m_pitch), -sinf (m_pitch), cosf (m_yaw) * cosf (m_pitch));

    SetView (m_eye, m_ahead, Math::Vec3::UnitY ());
}

}	// namespace GLngine
