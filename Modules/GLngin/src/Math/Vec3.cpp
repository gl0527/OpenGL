#include "Vec3.hpp"

#include <cmath>
#include "Math.hpp"


namespace GLngin {
namespace Math {

Vec3::Vec3 (float x0, float y0, float z0) :
    x (x0),
    y (y0),
    z (z0)
{
}


Vec3::Vec3 (float f /*= 0.0f*/) :
    x (f),
    y (f),
    z (f)
{
}


Vec3::Vec3 (float (&vec)[3]) :
    x (vec[0]),
    y (vec[1]),
    z (vec[2])
{
}


Vec3& Vec3::operator+ ()
{
    return *this;
}


Vec3 Vec3::operator+ (const Vec3& vec) const
{
    return Vec3 (x + vec.x, y + vec.y, z + vec.z);
}


Vec3& Vec3::operator+= (const Vec3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}


Vec3 Vec3::operator- () const
{
    return Vec3 (-x, -y, -z);
}


Vec3 Vec3::operator- (const Vec3& vec) const
{
    return Vec3 (x - vec.x, y - vec.y, z - vec.z);
}


Vec3& Vec3::operator-= (const Vec3& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}


Vec3& Vec3::operator*= (float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}


Vec3 Vec3::operator* (float scalar) const
{
    return Vec3 (x * scalar, y * scalar, z * scalar);
}


Vec3& Vec3::operator/= (float scalar)
{
    float scalarInv = 1 / scalar;
    x *= scalarInv;
    y *= scalarInv;
    z *= scalarInv;
    return *this;
}


Vec3 Vec3::operator/ (float scalar) const
{
    float scalarInv = 1 / scalar;
    return Vec3 (x * scalarInv, y * scalarInv, z * scalarInv);
}


bool Vec3::operator== (const Vec3& vec) const
{
    return IsEqual (x, vec.x) && IsEqual (y, vec.y) && IsEqual (z, vec.z);
}


bool Vec3::operator!= (const Vec3& vec) const
{
    return !IsEqual (x, vec.x) || !IsEqual (y, vec.y) || !IsEqual (z, vec.z);
}


float Vec3::Dot (const Vec3& vec) const
{
    return x * vec.x + y * vec.y + z * vec.z;
}


Vec3 Vec3::Hadamard (const Vec3& vec) const
{
    return Vec3 (x * vec.x, y * vec.y, z * vec.z);
}


Vec3 Vec3::Cross (const Vec3& vec) const
{
    return Vec3 (y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x);
}


float Vec3::Length () const
{
    return sqrtf (x * x + y * y + z * z);
}


float Vec3::LengthSqr () const
{
    return x * x + y * y + z * z;
}


Vec3 Vec3::Normalize () const
{
    return *this * (1 / (Length () + 1e-8f));
}


const Vec3& Vec3::Zero ()
{
    static Vec3 Zero;

    return Zero;
}


const Vec3& Vec3::One ()
{
    static Vec3 One (1.0f);

    return One;
}


const Vec3& Vec3::UnitX ()
{
    static Vec3 UnitX (1.0f, 0.0f, 0.0f);

    return UnitX;
}


const Vec3& Vec3::UnitY ()
{
    static Vec3 UnitY (0.0f, 1.0f, 0.0f);

    return UnitY;
}


const Vec3& Vec3::UnitZ ()
{
    static Vec3 UnitZ (0.0f, 0.0f, 1.0f);

    return UnitZ;
}


const Vec3& Vec3::NegativeUnitX ()
{
    static Vec3 NegativeUnitX (-1.0f, 0.0f, 0.0f);

    return NegativeUnitX;
}


const Vec3& Vec3::NegativeUnitY ()
{
    static Vec3 NegativeUnitY (0.0f, -1.0f, 0.0f);

    return NegativeUnitY;
}


const Vec3& Vec3::NegativeUnitZ ()
{
    static Vec3 NegativeUnitZ (0.0f, 0.0f, -1.0f);

    return NegativeUnitZ;
}

}   // namespace Math
}   // namespace GLngin
