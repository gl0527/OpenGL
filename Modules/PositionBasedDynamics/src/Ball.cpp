#include "Ball.hpp"

#include "Debug.hpp"
#include "Mat4.hpp"
#include "Sphere.hpp"
#include "RenderState.hpp"
#include "ShaderSamples.hpp"
#include "TextureCube.hpp"
#include <GL/glew.h>
#include <cstdio>
#include <cstring>

void Ball::InitImpl()
{
    const std::string currFolder(FOLDER);

    program.Init(GLngin::TransformVS, std::nullopt, std::nullopt, std::nullopt, GLngin::SmoothFS, std::nullopt);

    geometry.reset(new GLngin::Sphere(position, 0.5f));
    geometry->Init();
    ((GLngin::ParamSurface *)geometry.get())->Create(32, 32);

    std::string names[] = {
        currFolder + "../assets/morning_rt.tga",
        currFolder + "../assets/morning_lf.tga",
        currFolder + "../assets/morning_up.tga",
        currFolder + "../assets/morning_dn.tga",
        currFolder + "../assets/morning_bk.tga",
        currFolder + "../assets/morning_ft.tga"
    };

    program.Bind();
    program.SetUniformTextureCube("skybox", GLngin::TextureCube::GetID(names), 1);
    program.SetUniformVec3("idxOfRefr", GLngin::Math::Vec3(1.52f, 1.52f, 1.52f));
    program.SetUniformVec3("absorptCoeff", GLngin::Math::Vec3(0.0f, 0.0f, 0.0f));
    program.UnBind();
}

void Ball::DrawImpl(const GLngin::RenderState &renderState)
{
    const GLngin::Math::Mat4 M =    GLngin::Math::Mat4::Scale(scale) *
                                    GLngin::Math::Mat4::Rotate(rotAngle, rotAxis) *
                                    GLngin::Math::Mat4::Translate(position);

    const GLngin::Math::Mat4 Minv = GLngin::Math::Mat4::Translate(-position) *
                                    GLngin::Math::Mat4::Rotate(-rotAngle, rotAxis) *
                                    GLngin::Math::Mat4::Scale(GLngin::Math::Vec3(1 / scale.x, 1/ scale.y, 1 / scale.z));

    const GLngin::Math::Mat4 MVP = M * renderState.viewProj.value();

    program.Bind();
    program.SetUniformMat4("M", M);
    program.SetUniformMat4("Minv", Minv);
    program.SetUniformMat4("MVP", MVP);
    program.SetUniformVec4("eyePos", GLngin::Math::Vec4(renderState.cameraPos.value(), 1.0f));
    geometry->Draw();
    program.UnBind();
}
