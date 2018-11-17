#include "Camera.hpp"

#include <cmath>

#include "Mat4.hpp"


namespace GLngin {

Camera::Camera (float cX /*= 0.0f*/, float cY /*= 0.0f*/, float width /*= 0.0f*/, float height /*= 0.0f*/) :
    wCx (cX),
    wCy (cY),
    wWx (width),
    wWy (height)
{
	Animate (0);
}


Math::Mat4 Camera::V ()
{
    return Math::Mat4 (	1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
                    -wCx, -wCy, 0, 1);
}


Math::Mat4 Camera::P ()
{
    return Math::Mat4(2/wWx,    0, 0, 0,
			        0,    2/wWy, 0, 0,
			        0,        0, 1, 0,
			        0,        0, 0, 1);
}


Math::Mat4 Camera::Vinv ()
{
    return Math::Mat4(1,     0, 0, 0,
				    0,     1, 0, 0,
			        0,     0, 1, 0,
                    wCx, wCy, 0, 1);
}


Math::Mat4 Camera::Pinv ()
{
    return Math::Mat4(wWx/2, 0,    0, 0,
			           0, wWy/2, 0, 0,
			           0,  0,    1, 0,
			           0,  0,    0, 1);
}


void Camera::Animate (float t)
{
    wCx = 10 * cosf(t);
	wCy = 0;
	wWx = 20;
	wWy = 20;
}

}	// namespace GLngine
