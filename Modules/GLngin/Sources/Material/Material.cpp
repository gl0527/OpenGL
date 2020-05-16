#include "Material/Material.hpp"

#include "Shader.hpp"

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