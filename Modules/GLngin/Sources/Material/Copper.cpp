#include "Copper.hpp"

#include "TextureCube.hpp"
#include "Vec3.hpp"

namespace GLngin {
namespace Material {

void Copper::Bind()
{
    shader.Bind();
    shader.SetUniformTextureCube("skybox", GLngin::TextureCube::GetID(names), 1);
    shader.SetUniformVec3("idxOfRefr", GLngin::Math::Vec3(0.2f, 1.1f, 1.2f));
    shader.SetUniformVec3("absorptCoeff", GLngin::Math::Vec3(3.6f, 2.6f, 2.3f));
}

}  // namespace Material
}  // namespace GLngin
