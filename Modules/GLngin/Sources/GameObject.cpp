#include "GameObject.hpp"

#include "Geometry.hpp"
#include "Mat4.hpp"

namespace GLngin {

GameObject::GameObject(const std::string &_id, const std::shared_ptr<Material::Material> &_material,
                       const Math::Vec3 &_position /*= Math::Vec3::Zero ()*/, float _rotAngle /*= 0.0f*/,
                       const Math::Vec3 &_rotAxis /*= Math::Vec3::UnitY ()*/)
    : id(_id)
    , position(_position)
    , velocity(Math::Vec3::Zero())
    , acceleration(Math::Vec3::Zero())
    , rotAxis(_rotAxis)
    , rotAngle(_rotAngle)
    , scale(Math::Vec3::One())
    , geometry(nullptr)
    , material(_material)
{
}

GameObject::~GameObject()
{
}

const std::string &GameObject::GetId() const
{
    return id;
}

bool GameObject::AddChild(const std::shared_ptr<GameObject> &child)
{
    if (children.find(child->id) == children.end()) {
        children[child->id] = child;
        return true;
    }
    return false;
}

bool GameObject::RemoveChild(const std::string &_id)
{
    if (children.find(_id) != children.end()) {
        children.erase(_id);
        return true;
    } else {
        return false;
    }
}

void GameObject::GetTransform(Math::Mat4 &M, Math::Mat4 &Minv) const
{
    M = Math::Mat4::Scale(scale) * Math::Mat4::Rotate(rotAngle, rotAxis) * Math::Mat4::Translate(position);
    Minv = Math::Mat4::Translate(-position) * Math::Mat4::Rotate(-rotAngle, rotAxis) *
           Math::Mat4::Scale(Math::Vec3(1 / scale.x, 1 / scale.y, 1 / scale.z));
}

void GameObject::Init()
{
    InitImpl();
    for (auto &[_id, _child] : children) {
        _child->Init();
    }
}

void GameObject::Interact(GameObject *other)
{
    InteractImpl(other);
    for (auto &[_id, _child] : children) {
        _child->Interact(other);
    }
}

void GameObject::Control(float t, float dt, const InputManager &input)
{
    ControlImpl(t, dt, input);
    for (auto &[_id, _child] : children) {
        _child->Control(t, dt, input);
    }
}

void GameObject::Animate(float t, float dt)
{
    AnimateImpl(t, dt);
    for (auto &[_id, _child] : children) {
        _child->Animate(t, dt);
    }
}

void GameObject::Draw(const PerFrameData &pfd)
{
    DrawImpl(pfd);
    for (const auto &[_id, _child] : children) {
        _child->Draw(pfd);
    }
}

void GameObject::Terminate()
{
    TerminateImpl();
    for (auto &[_id, _child] : children) {
        _child->Terminate();
    }
}

}  // namespace GLngin