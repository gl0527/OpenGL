#include "Smooth.hpp"

#include "ShaderSamples.hpp"
#include "RenderState.hpp"

namespace GLngin {
namespace Material {

Smooth::Smooth(const std::string (&_names)[6])
{
    shader.Init(TransformVS, std::nullopt, std::nullopt, std::nullopt, SmoothFS, std::nullopt);
    for (unsigned char i = 0; i < 6; ++i) {
        names[i] = _names[i];
    }
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
