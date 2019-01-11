#pragma once

#ifndef GLNGIN_CAMERA_HPP
#define GLNGIN_CAMERA_HPP

#include "API.hpp"
#include "Mat4.hpp"
#include "Vec3.hpp"


namespace GLngin {

// TODO splines
// TODO cinematic
class GLNGIN_API Camera {
public:
                        Camera (const Math::Vec3& eye, const Math::Vec3& ahead, const Math::Vec3& up);

    const Math::Vec3&   GetPosition () const;
    const Math::Vec3&   GetDirection () const;

    const Math::Mat4&   GetViewMatrix () const;
    const Math::Mat4&   GetProjMatrix () const;

    void                SetView (const Math::Vec3& eye, const Math::Vec3& ahead, const Math::Vec3& up);
    void                SetProj (float fov, float aspect, float nearPlane, float farPlane);
    void                SetAspect (float aspect);
    void                LookAt (const Math::Vec3& target);

    void                Animate (float dt);

private:
    Math::Vec3 m_eye;
    Math::Vec3 m_ahead;
    Math::Vec3 m_right;
    Math::Vec3 m_up;

    Math::Mat4 m_viewMat;
    Math::Mat4 m_projMat;

    float m_yaw;
    float m_pitch;
    float m_fov;
    float m_aspect;
    float m_front;
    float m_back;

    void UpdateProj ();
};

}   // namespace GLngine

#endif  // #ifndef GLNGIN_CAMERA_HPP
