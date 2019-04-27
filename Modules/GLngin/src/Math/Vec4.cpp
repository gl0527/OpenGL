#include "Vec4.hpp"
#include "Mat4.hpp"


namespace GLngin {
namespace Math {

Vec4 Vec4::operator* (const Mat4& mat) const
{
    return Vec4 (Dot (mat.GetCol (0)), Dot (mat.GetCol (1)), Dot (mat.GetCol (2)), Dot (mat.GetCol (3)));
}

}   // namespace Math
}   // namespace GLngin