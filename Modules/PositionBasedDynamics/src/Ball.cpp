#include "Ball.hpp"

#include "Material/Material.hpp"
#include "Sphere.hpp"
#include "RenderState.hpp"

void Ball::InitImpl()
{
    const std::string currFolder(FOLDER);

    auto sphere = std::make_unique<GLngin::Sphere>(position, 0.5f);
    sphere->Init();
    sphere->Create(32, 32);

    geometry = std::move(sphere);

    material->Bind();
    material->UnBind();
}

void Ball::DrawImpl(const GLngin::PerFrameData &pfd)
{
    GLngin::PerObjectData pod;
    GetTransform(pod.M, pod.Minv);
    pod.MVP = pod.M * pfd.VP;

    material->Bind(pod, pfd);
    geometry->Draw();
    material->UnBind();
}
