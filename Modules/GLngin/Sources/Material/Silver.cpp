#include "Silver.hpp"

#include "TextureCube.hpp"
#include "Vec3.hpp"

namespace GLngin {
namespace Material {

void Silver::Bind()
{
    shader.Bind();
    shader.SetUniformTextureCube("skybox", GLngin::TextureCube::GetID(names), 1);
    shader.SetUniformVec3("idxOfRefr", GLngin::Math::Vec3(0.14f, 0.16f, 0.13f));
    shader.SetUniformVec3("absorptCoeff", GLngin::Math::Vec3(4.1f, 2.3f, 3.1f));
}

}  // namespace Material
}  // namespace GLngin
