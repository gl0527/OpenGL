#include "Material/Material.hpp"

namespace GLngin {
namespace Material {

Material::~Material()
{
}

void Material::UnBind()
{
    shader.UnBind();
}

}  // namespace Material
}  // namespace GLngin