#include "GameObject.hpp"

#include "Geometry.hpp"


namespace GLngin {

GameObject::GameObject (const std::string& _id, const Math::Vec3& _position /*= Math::Vec3::Zero ()*/, float _rotAngle /*= 0.0f*/, const Math::Vec3& _rotAxis /*= Math::Vec3::UnitY ()*/) :
    id (_id),
    position (_position),
    velocity (Math::Vec3::Zero ()),
    acceleration (Math::Vec3::Zero ()),
    rotAxis (_rotAxis),
    rotAngle (_rotAngle),
    scale (Math::Vec3::One ()),
    geometry (nullptr)
{
}


GameObject::~GameObject ()
{
}


bool GameObject::AddChild (const std::shared_ptr<GameObject>& child)
{
    if (children.find (child->id) == children.end ()) {
        children[child->id] = child;
        return true;
    }
    return false;
}


bool GameObject::RemoveChild (const std::string& id)
{
    if (children.find (id) != children.end ()) {
        children.erase (id);
        return true;
    } else {
        return false;
    }
}


void GameObject::Init ()
{
    InitImpl ();
    for (auto& [id, child] : children)
        child->Init ();
}


void GameObject::Interact (GameObject* other)
{
    InteractImpl (other);
    for (auto& [id, child] : children)
        child->Interact (other);
}


void GameObject::Control (float t, float dt)
{
    ControlImpl (t, dt);
    for (auto& [id, child] : children)
        child->Control (t, dt);
}


void GameObject::Animate (float t, float dt)
{
    AnimateImpl (t, dt);
    for (auto& [id, child] : children)
        child->Animate (t, dt);
}


void GameObject::Draw (const Camera* const camera) const
{
    DrawImpl (camera);
    for (const auto& [id, child] : children)
        child->Draw (camera);
}

}   // namespace GLngin