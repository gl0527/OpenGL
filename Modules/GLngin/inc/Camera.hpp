#pragma once

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Mat4.hpp"
#include "Vec4.hpp"


namespace GLngin {

class Cam {
public:
    Cam ();

    const Vec4& GetPosition () const;
    const Vec4& GetAhead () const;

    const Mat4& GetViewMatrix () const;
    const Mat4& GetProjMatrix () const;
    const Mat4& GetRayDirMatrix () const;

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
    Vec4 m_position;
    Vec4 m_ahead;
    Vec4 m_up;
    Mat4 m_viewMat;
    Mat4 m_rayDirMat;
    Mat4 m_projMat;

    void CalcViewMatrix ();
    void CalcProjMatrix ();
};

struct Camera {
	Camera ();

	Mat4 V();
	Mat4 P();

	Mat4 Vinv();
	Mat4 Pinv();

    void Animate(float t);
	
private:
	float wCx, wCy;	// center in world coordinates
	float wWx, wWy;	// width and height in world coordinates
};

}	// namespace GLngine

#endif	// #ifndef CAMERA_HPP
