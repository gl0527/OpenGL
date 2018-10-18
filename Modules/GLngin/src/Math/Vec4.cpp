#include "Vec4.hpp"

#include <cassert>
#include <cmath>

#include "Mat4.hpp"
#include "Math.hpp"


namespace GLngin {
namespace Math {

Vec4::Vec4 (float x0, float y0, float z0, float w0) :
    x (x0),
    y (y0),
    z (z0),
    w (w0)
{
}


Vec4::Vec4 (float f/*= 0.0f*/) :
    x (f),
    y (f),
    z (f),
    w (f)
{
}


Vec4::Vec4 (float (&vec)[4]) :
    x (vec[0]),
    y (vec[1]),
    z (vec[2]),
    w (vec[3])
{
}


Vec4& Vec4::operator+ ()
{
    return *this;
}


Vec4 Vec4::operator+ (const Vec4& vec) const
{
    return Vec4 (x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}


Vec4& Vec4::operator+= (const Vec4& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;
    return *this;
}


Vec4 Vec4::operator- ()
{
    return Vec4 (-x, -y, -z, -w);
}


Vec4 Vec4::operator- (const Vec4& vec) const
{
    return Vec4 (x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}


Vec4& Vec4::operator-= (const Vec4& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;
    return *this;
}


Vec4& Vec4::operator*= (float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}


Vec4 Vec4::operator* (float scalar) const
{
    return Vec4 (x * scalar, y * scalar, z * scalar, w * scalar);
}


Vec4 Vec4::operator* (const Mat4& mat) const
{
    return Vec4 (   Dot (Vec4 (mat[0][0], mat[1][0], mat[2][0], mat[3][0])),
                    Dot (Vec4 (mat[0][1], mat[1][1], mat[2][1], mat[3][1])),
                    Dot (Vec4 (mat[0][2], mat[1][2], mat[2][2], mat[3][2])),
                    Dot (Vec4 (mat[0][3], mat[1][3], mat[2][3], mat[3][3])));
}


Vec4& Vec4::operator/= (float scalar)
{
    assert (fabsf (scalar) > 1e-6f);
    float scalarInv = 1 / scalar;
    x *= scalarInv;
    y *= scalarInv;
    z *= scalarInv;
    w *= scalarInv;
    return *this;
}


Vec4 Vec4::operator/ (float scalar) const
{
    assert (fabsf (scalar) > 1e-6f);
    float scalarInv = 1 / scalar;
    return Vec4 (x * scalarInv, y * scalarInv, z * scalarInv, w * scalarInv);
}


bool Vec4::operator== (const Vec4& vec) const
{
    return  IsEqual (x, vec.x) &&
            IsEqual (y, vec.y) &&
            IsEqual (z, vec.z) &&
            IsEqual (w, vec.w);
}


bool Vec4::operator!= (const Vec4& vec) const
{
    return  !IsEqual (x, vec.x) ||
            !IsEqual (y, vec.y) ||
            !IsEqual (z, vec.z) ||
            !IsEqual (w, vec.w);
}


float Vec4::Dot (const Vec4& vec) const
{
    return x*vec.x + y*vec.y + z*vec.z + w*vec.w;
}


Vec4 Vec4::Hadamard (const Vec4& vec) const
{
    return Vec4 (x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}


const Vec4& Vec4::Zero ()
{
    static Vec4 Zero (0.0f, 0.0f, 0.0f, 0.0f);

    return Zero;
}


const Vec4& Vec4::One ()
{
    static Vec4 One (1.0f, 1.0f, 1.0f, 1.0f);

    return One;
}


const Vec4& Vec4::UnitX ()
{
    static Vec4 UnitX (1.0f, 0.0f, 0.0f, 0.0f);

    return UnitX;
}


const Vec4& Vec4::UnitY ()
{
    static Vec4 UnitY (0.0f, 1.0f, 0.0f, 0.0f);

    return UnitY;
}


const Vec4& Vec4::UnitZ ()
{
    static Vec4 UnitZ (0.0f, 0.0f, 1.0f, 0.0f);

    return UnitZ;
}


const Vec4& Vec4::UnitW ()
{
    static Vec4 UnitW (0.0f, 0.0f, 0.0f, 1.0f);

    return UnitW;
}


const Vec4& Vec4::NegativeUnitX ()
{
    static Vec4 NegativeUnitX (-1.0f, 0.0f, 0.0f, 0.0f);

    return NegativeUnitX;
}


const Vec4& Vec4::NegativeUnitY ()
{
    static Vec4 NegativeUnitY (0.0f, -1.0f, 0.0f, 0.0f);

    return NegativeUnitY;
}


const Vec4& Vec4::NegativeUnitZ ()
{
    static Vec4 NegativeUnitZ (0.0f, 0.0f, -1.0f, 0.0f);

    return NegativeUnitZ;
}


const Vec4& Vec4::NegativeUnitW ()
{
    static Vec4 NegativeUnitW (0.0f, 0.0f, 0.0f, -1.0f);

    return NegativeUnitW;
}

}   // namespace Math
}	// namespace GLngine
