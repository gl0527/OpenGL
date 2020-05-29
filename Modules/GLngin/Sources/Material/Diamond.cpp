#include "Diamond.hpp"

#include "TextureCube.hpp"
#include "Vec3.hpp"

namespace GLngin {
namespace Material {

void Diamond::Bind()
{
    shader.Bind();
    shader.SetUniformTextureCube("skybox", GLngin::TextureCube::GetID(names), 1);
    shader.SetUniformVec3("idxOfRefr", GLngin::Math::Vec3(2.4f, 2.4f, 2.4f));
    shader.SetUniformVec3("absorptCoeff", GLngin::Math::Vec3(0.0f, 0.0f, 0.0f));
}

}  // namespace Material
}  // namespace GLngin
