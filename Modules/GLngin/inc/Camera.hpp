#pragma once

#ifndef GLNGIN_CAMERA_HPP
#define GLNGIN_CAMERA_HPP

#include "Mat4.hpp"
#include "Vec4.hpp"


namespace GLngin {

class Camera {
public:
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
