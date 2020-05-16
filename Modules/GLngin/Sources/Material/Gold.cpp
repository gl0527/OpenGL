#include "Material/Gold.hpp"

#include "ShaderSamples.hpp"
#include "TextureCube.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"
#include "RenderState.hpp"

namespace GLngin {
namespace Material {

Gold::Gold(const std::string (&_names)[6])
{
    shader.Init(TransformVS, std::nullopt, std::nullopt, std::nullopt, SmoothFS, std::nullopt);
    for (unsigned char i = 0; i < 6; ++i) {
        names[i] = _names[i];
    }
}

void Gold::Bind()
{
    shader.Bind();
    shader.SetUniformTextureCube("skybox", GLngin::TextureCube::GetID(names), 1);
    shader.SetUniformVec3("idxOfRefr", GLngin::Math::Vec3(0.17f, 0.35f, 1.5f));
    shader.SetUniformVec3("absorptCoeff", GLngin::Math::Vec3(3.1f, 2.7f, 1.9f));
}

void Gold::Bind(const PerObjectData &pod, const PerFrameData &pfd)
{
    shader.Bind();
    shader.SetUniformMat4("M", pod.M);
    shader.SetUniformMat4("Minv", pod.Minv);
    shader.SetUniformMat4("MVP", pod.MVP);
    shader.SetUniformVec4("eyePos", GLngin::Math::Vec4(pfd.wEye, 1.0f));
}

}  // namespace Material
}  // namespace GLngin