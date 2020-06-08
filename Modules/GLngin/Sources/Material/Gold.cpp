#include "Gold.hpp"

#include "Vec3.hpp"

namespace GLngin {
namespace Material {

Gold::Gold(const std::string (&_names)[6])
    : Smooth(_names, Math::Vec3(0.17f, 0.35f, 1.5f), Math::Vec3(3.1f, 2.7f, 1.9f))
{
}

}  // namespace Material
}  // namespace GLngin