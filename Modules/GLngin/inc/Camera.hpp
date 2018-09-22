#pragma once

#ifndef GLNGIN_CAMERA_HPP
#define GLNGIN_CAMERA_HPP

#include "Mat4.hpp"
#include "Vec4.hpp"


namespace GLngin {

class Cam {
public:
    Cam ();

    const Math::Vec4& GetPosition () const;
    const Math::Vec4& GetAhead () const;

    const Math::Mat4& GetViewMatrix () const;
    const Math::Mat4& GetProjMatrix () const;
    const Math::Mat4& GetRayDirMatrix () const;

    void Animate (double dt);

private:
    float yaw;
    float pitch;
    float fov;
    float aspect;
    float nearPlane;
    float farPlane;
    float speed;
    bool m_keys[256];
    Math::Vec4 m_position;
    Math::Vec4 m_ahead;
    Math::Vec4 m_up;
    Math::Mat4 m_viewMat;
    Math::Mat4 m_rayDirMat;
    Math::Mat4 m_projMat;

    void CalcViewMatrix ();
    void CalcProjMatrix ();
};

struct Camera {
	Camera ();

    Math::Mat4 V();
    Math::Mat4 P();

    Math::Mat4 Vinv();
    Math::Mat4 Pinv();

    void Animate(float t);
	
private:
	float wCx, wCy;	// center in world coordinates
	float wWx, wWy;	// width and height in world coordinates
};

}	// namespace GLngine

#endif	// #ifndef GLNGIN_CAMERA_HPP
