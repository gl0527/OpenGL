#include "Silver.hpp"

#include "Vec3.hpp"

namespace GLngin {
namespace Material {

Silver::Silver(const std::string (&_names)[6])
    : Smooth(_names, Math::Vec3(0.14f, 0.16f, 0.13f), Math::Vec3(4.1f, 2.3f, 3.1f))
{
}

}  // namespace Material
}  // namespace GLngin
