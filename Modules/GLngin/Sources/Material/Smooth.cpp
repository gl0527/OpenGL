#include "Smooth.hpp"

#include "ShaderSamples.hpp"
#include "RenderState.hpp"
#include "TextureCube.hpp"

namespace GLngin {
namespace Material {

Smooth::Smooth(const std::string (&_names)[6], const Math::Vec3 &_idxOfRefr, const Math::Vec3 &_absorptCoeff)
    : idxOfRefr(_idxOfRefr)
    , absorptCoeff(_absorptCoeff)
{
    shader.Init(TransformVS, std::nullopt, std::nullopt, std::nullopt, SmoothFS, std::nullopt);
    for (unsigned char i = 0; i < 6; ++i) {
        names[i] = _names[i];
    }
}

void Smooth::Bind()
{
    shader.Bind();
    shader.SetUniformTextureCube("skybox", TextureCube::GetID(names), 1);
    shader.SetUniformVec3("idxOfRefr", idxOfRefr);
    shader.SetUniformVec3("absorptCoeff", absorptCoeff);
}

void Smooth::Bind(const PerObjectData &pod, const PerFrameData &pfd)
{
    shader.Bind();
    shader.SetUniformMat4("M", pod.M);
    shader.SetUniformMat4("Minv", pod.Minv);
    shader.SetUniformMat4("MVP", pod.MVP);
    shader.SetUniformVec3("eyePos", pfd.wEye);
}

}  // namespace Material
}  // namespace GLngin
