#include "Gold.hpp"

#include "TextureCube.hpp"
#include "Vec3.hpp"

namespace GLngin {
namespace Material {

void Gold::Bind()
{
    shader.Bind();
    shader.SetUniformTextureCube("skybox", GLngin::TextureCube::GetID(names), 1);
    shader.SetUniformVec3("idxOfRefr", GLngin::Math::Vec3(0.17f, 0.35f, 1.5f));
    shader.SetUniformVec3("absorptCoeff", GLngin::Math::Vec3(3.1f, 2.7f, 1.9f));
}

}  // namespace Material
}  // namespace GLngin