#include "Skybox.hpp"

#include "ShaderSamples.hpp"
#include "TextureCube.hpp"
#include "RenderState.hpp"

namespace GLngin {
namespace Material {

Skybox::Skybox(const std::string (&_names)[6])
{
    shader.Init(BackgroundVS, std::nullopt, std::nullopt, std::nullopt, BackgroundFS, std::nullopt);
    for (unsigned char i = 0; i < 6; ++i) {
        names[i] = _names[i];
    }
}

void Skybox::Bind()
{
    shader.Bind();
    shader.SetUniformTextureCube("skybox", GLngin::TextureCube::GetID(names), 0);
}

void Skybox::Bind(const PerObjectData &pod, const PerFrameData &pfd)
{
    shader.Bind();
    shader.SetUniformMat4("MVP", pod.MVP);
}

}  // namespace Material
}  // namespace GLngin
