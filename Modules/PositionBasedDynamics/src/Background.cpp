#include "Background.hpp"

#include "Mat4.hpp"
#include "Material/Material.hpp"
#include "RenderState.hpp"

Background::Background(const std::string &id, const std::shared_ptr<GLngin::Material::Material> &_material,
                       const std::string (&_names)[6])
    : GameObject(id, _material, GLngin::Math::Vec3(0, 0, 0))
{
    for (unsigned char i = 0; i < 6; ++i) {
        names[i] = _names[i];
    }
}

void Background::InitImpl()
{
    cube.Init(50);
    material->Bind();
    material->UnBind();
}

void Background::DrawImpl(const GLngin::PerFrameData &pfd)
{
    GLngin::PerObjectData pod;
    pod.M = GLngin::Math::Mat4::Translate(pfd.wEye);
    pod.MVP = pod.M * pfd.VP;

    material->Bind(pod, pfd);
    cube.Render();
    material->UnBind();
}
