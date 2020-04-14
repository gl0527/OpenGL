#include "Background.hpp"

#include "Debug.hpp"
#include "Mat4.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "RenderState.hpp"
#include "ShaderSamples.hpp"
#include "TextureCube.hpp"
#include <GL/glew.h>
#include <cstdio>
#include <cstring>

Background::Background(const std::string &id, const std::string &right, const std::string &left, const std::string &top,
                       const std::string &bottom, const std::string &front, const std::string &back)
    : GameObject(id, GLngin::Math::Vec3(0, 0, 0))
    , names{right, left, top, bottom, front, back}
{
}

void Background::InitImpl()
{
    const std::string currFolder(FOLDER);
    program.Init(GLngin::BackgroundVS, std::nullopt, std::nullopt, std::nullopt, GLngin::BackgroundFS, std::nullopt);
    cube.Init(50);
    program.Bind();
    program.SetUniformTextureCube("skybox", GLngin::TextureCube::GetID(names), 0);
    program.UnBind();
}

void Background::DrawImpl(const GLngin::RenderState &renderState)
{
    program.Bind();
    program.SetUniformMat4("MVP",
                           GLngin::Math::Mat4::Translate(renderState.cameraPos.value()) * renderState.viewProj.value());
    cube.Render();
    program.UnBind();
}
