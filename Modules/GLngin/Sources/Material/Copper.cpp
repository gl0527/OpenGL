#include "Copper.hpp"

#include "Vec3.hpp"

namespace GLngin {
namespace Material {

Copper::Copper(const std::string (&_names)[6])
    : Smooth(_names, Math::Vec3(0.2f, 1.1f, 1.2f), Math::Vec3(3.6f, 2.6f, 2.3f))
{
}

}  // namespace Material
}  // namespace GLngin
