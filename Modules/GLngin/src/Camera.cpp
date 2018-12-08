#include "Camera.hpp"

#include <cmath>

#include "Mat4.hpp"
#include "Math.hpp"
#include "Vec4.hpp"
#include "InputManager.hpp"


namespace GLngin {

Camera::Camera () :
    m_eye (Math::Vec3::Zero ()),
    m_ahead (Math::Vec3::NegativeUnitZ ()),
    m_right (Math::Vec3::UnitX ()),
    m_yaw (0.0f),
    m_pitch (0.0f),
    m_fov (Math::AngleToRadian (90)),
    m_aspect (1.0f),
    m_front (0.1f),
    m_back (100.0f)
{
    SetAspect (m_aspect);

    Math::Vec3 zAxis = m_ahead.Normalize ();
    Math::Vec3 xAxis = zAxis.Cross (Math::Vec3::UnitY ()).Normalize ();
    Math::Vec3 yAxis = xAxis.Cross (zAxis);

    m_viewMat = Math::Mat4 (xAxis.x,                    yAxis.x,                zAxis.x,                0.0f,
                            xAxis.y,                    yAxis.y,                zAxis.y,                0.0f,
                            xAxis.z,                    yAxis.z,                zAxis.z,                0.0f,
                            -xAxis.Dot (m_eye),   -yAxis.Dot (m_eye), -zAxis.Dot (m_eye),1.0f);

    const Math::Vec3& Zero = Math::Vec3::Zero ();
    Math::Mat4 mat = Math::Mat4 (xAxis.x,           yAxis.x,            zAxis.x,            0.0f,
                                 xAxis.y,           yAxis.y,            zAxis.y,            0.0f,
                                 xAxis.z,           yAxis.z,            zAxis.z,            0.0f,
                                 -xAxis.Dot (Zero), -yAxis.Dot (Zero), -zAxis.Dot (Zero),   1.0f);

    m_rayDirMat = (mat * m_projMat).Invert ();
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


const Math::Mat4& Camera::GetRayDirMatrix () const
{
    return m_rayDirMat;
}


void Camera::UpdateView ()
{
    Math::Vec3 zAxis = m_ahead.Normalize ();
    Math::Vec3 xAxis = zAxis.Cross (Math::Vec3::UnitY ()).Normalize ();
    Math::Vec3 yAxis = xAxis.Cross (zAxis);

    m_viewMat = Math::Mat4 (xAxis.x,                    yAxis.x,                zAxis.x,                0.0f,
                            xAxis.y,                    yAxis.y,                zAxis.y,                0.0f,
                            xAxis.z,                    yAxis.z,                zAxis.z,                0.0f,
                            -xAxis.Dot (m_eye),   -yAxis.Dot (m_eye), -zAxis.Dot (m_eye),1.0f);

    const Math::Vec3& Zero = Math::Vec3::Zero ();
    Math::Mat4 mat = Math::Mat4 (xAxis.x,           yAxis.x,            zAxis.x,            0.0f,
                                 xAxis.y,           yAxis.y,            zAxis.y,            0.0f,
                                 xAxis.z,           yAxis.z,            zAxis.z,            0.0f,
                                 -xAxis.Dot (Zero), -yAxis.Dot (Zero), -zAxis.Dot (Zero),   1.0f);

    m_rayDirMat = (mat * m_projMat).Invert ();

    m_right = Math::Vec3::UnitY ().Cross (m_ahead).Normalize ();
    m_yaw = ::atan2f (m_ahead.x, m_ahead.z);
    m_pitch = -::atan2f (m_ahead.y, ::sqrtf (m_ahead.x * m_ahead.x + m_ahead.z * m_ahead.z));
}


void Camera::UpdateProj ()
{
    float yScale = 1 / ::tanf (m_fov * 0.5f);
    float xScale = yScale / m_aspect;
    float f = m_back;
    float n = m_front;

    m_projMat = Math::Mat4 (xScale, 0.0f,   0.0f,          0.0f,
                            0.0f,   yScale, 0.0f,          0.0f,
                            0.0f,   0.0f,   f/(f-n),       1.0f,
                            0.0f,   0.0f,   -n*f/(f-n),    0.0f);
}


void Camera::SetView (const Math::Vec3& eye, const Math::Vec3& ahead)
{
    m_eye = eye;
    m_ahead = ahead;
    UpdateView ();
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


void Camera::Animate (float dt)
{
    if (InputManager::Instance ().IsKeyDown (InputManager::KeyCode::KC_w)) {
        m_eye += m_ahead * 0.001f * dt;
    }
    if (InputManager::Instance ().IsKeyDown (InputManager::KeyCode::KC_s)) {
        m_eye -= m_ahead * 0.001f * dt;
    }
    if (InputManager::Instance ().IsKeyDown (InputManager::KeyCode::KC_a)) {
        m_eye += m_right * 0.001f * dt;
    }
    if (InputManager::Instance ().IsKeyDown (InputManager::KeyCode::KC_d)) {
        m_eye -= m_right * 0.001f * dt;
    }

    int dx, dy;
    InputManager::Instance ().GetMouseDelta (&dx, &dy);

    m_yaw += 0.01f * dx;
    m_pitch += 0.01f * dy;

    if (m_pitch < -Math::Pi * 0.5f)
        m_pitch = -Math::Pi * 0.5f;
    else if (m_pitch > Math::Pi * 0.5f)
        m_pitch = Math::Pi * 0.5f;

    m_ahead = Math::Vec3 (::sinf (m_yaw) * ::cosf (m_pitch), -::sinf (m_pitch), ::cosf (m_yaw) * ::cosf (m_pitch));

    UpdateView ();
}

}	// namespace GLngine
