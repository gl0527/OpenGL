#pragma once

#ifndef GLNGIN_CAMERA_HPP
#define GLNGIN_CAMERA_HPP

#include "API.hpp"


namespace GLngin {
namespace Math {
    class Mat4;
}   // namespace Math


// TODO Vec3
// TODO splines
// TODO cinematic
class GLNGIN_API Camera {
public:
    Camera (float cX = 0.0f, float cY = 0.0f, float width = 0.0f, float height = 0.0f);

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
