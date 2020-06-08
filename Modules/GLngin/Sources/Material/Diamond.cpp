#include "Diamond.hpp"

#include "Vec3.hpp"

namespace GLngin {
namespace Material {

Diamond::Diamond(const std::string (&_names)[6])
    : Smooth(_names, Math::Vec3(2.4f, 2.4f, 2.4f), Math::Vec3(0.0f, 0.0f, 0.0f))
{
}

}  // namespace Material
}  // namespace GLngin
