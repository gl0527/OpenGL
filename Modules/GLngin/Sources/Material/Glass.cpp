#include "Glass.hpp"

#include "Vec3.hpp"

namespace GLngin {
namespace Material {

Glass::Glass(const std::string (&_names)[6])
    : Smooth(_names, Math::Vec3(1.5f, 1.5f, 1.5f), Math::Vec3(0.0f, 0.0f, 0.0f))
{
}

}  // namespace Material
}  // namespace GLngin
