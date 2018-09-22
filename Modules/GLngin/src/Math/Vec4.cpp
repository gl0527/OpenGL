#include "Vec4.hpp"

#include <cassert>
#include <cmath>

#include "Mat4.hpp"
#include "Math.hpp"


namespace GLngin {
namespace Math {

Vec4::Vec4 (float x0/*=0.0f*/, float y0/*=0.0f*/, float z0/*=0.0f*/, float w0/*=1.0f*/) :
    m_array {x0, y0, z0, w0},
    x (m_array[0]),
    y (m_array[1]),
    z (m_array[2]),
    w (m_array[3])
{
}


Vec4::Vec4 (float (&vec)[4]) :
    m_array {vec[0], vec[1], vec[2], vec[3]},
    x (m_array[0]),
    y (m_array[1]),
    z (m_array[2]),
    w (m_array[3])
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
    Vec4 result;
    for (unsigned char j = 0; j < 4; j++) {
        result.m_array[j] = 0;
        for (unsigned char i = 0; i < 4; i++)
            result.m_array[j] += m_array[i] * mat[i][j];
    }
    return result;
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


float Vec4::operator[] (unsigned char idx) const
{
    return m_array[idx];
}


float& Vec4::operator[] (unsigned char idx)
{
    return m_array[idx];
}


Vec4::operator const float* () const
{
    return m_array;
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
