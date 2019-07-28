#pragma once

#ifndef GLNGIN_GAMEOBJECT_HPP
#define GLNGIN_GAMEOBJECT_HPP

#include "API.hpp"
#include "Vec3.hpp"
#include "Program.hpp"
#include <unordered_map>
#include <memory>


namespace GLngin {

class Geometry;
class Camera;

class GLNGIN_API GameObject : public std::enable_shared_from_this<GameObject> {
public:
    GameObject (const std::string& _id, const Math::Vec3& _position = Math::Vec3::Zero (), float _rotAngle = 0.0f, const Math::Vec3& _rotAxis = Math::Vec3::UnitY ());
    virtual ~GameObject ();

    bool AddChild (const std::shared_ptr<GameObject>& child);
    bool RemoveChild (const std::string& id);

    void Init ();
    void Interact (GameObject* other);
    void Control (float t, float dt);
    void Animate (float t, float dt);
    void Draw (const Camera* const camera) const;

protected:
    virtual void InitImpl () {}
    virtual void InteractImpl (GameObject* /* other */) {}
    virtual void ControlImpl (float /* t */, float /* dt */) {}
    virtual void AnimateImpl (float /* t */, float /* dt */) {}
    virtual void DrawImpl (const Camera* const /* camera */) const {}

protected:
    using ChildrenMap = std::unordered_map<std::string, std::shared_ptr<GameObject>>;

    const std::string id;

    Math::Vec3 position;
    Math::Vec3 velocity;
    Math::Vec3 acceleration;
    Math::Vec3 rotAxis;
    float rotAngle;
    Math::Vec3 scale;

    Program program;
    std::unique_ptr<Geometry> geometry;
    ChildrenMap children;
};

}   // namespace GLngin

#endif  // #ifndef GLNGIN_GAMEOBJECT_HPP
