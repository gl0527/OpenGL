#include "Camera.hpp"
#include "Mat4.hpp"


namespace GLngin {

Camera::Camera ()
{
	Animate (0);
}


Mat4 Camera::V ()
{
	return Mat4 (	1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					-wCx, -wCy, 0, 1);
}


Mat4 Camera::P ()
{
	return Mat4(2/wWx,    0, 0, 0,
			        0,    2/wWy, 0, 0,
			        0,        0, 1, 0,
			        0,        0, 0, 1);
}


Mat4 Camera::Vinv ()
{
	return Mat4(1,     0, 0, 0,
				    0,     1, 0, 0,
			        0,     0, 1, 0,
					wCx, wCy, 0, 1);
}


Mat4 Camera::Pinv ()
{
	return Mat4(wWx/2, 0,    0, 0,
			           0, wWy/2, 0, 0,
			           0,  0,    1, 0,
			           0,  0,    0, 1);
}


void Camera::Animate (float /*t*/)
{
	wCx = 0; // 10 * cosf(t);
	wCy = 0;
	wWx = 20;
	wWy = 20;
}

}	// namespace GLngine
