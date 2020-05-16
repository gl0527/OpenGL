#pragma once

#ifndef GLNGIN_SCENE_HPP
#define GLNGIN_SCENE_HPP

#include <unordered_map>
#include <memory>
#include "API.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "RenderState.hpp"

namespace GLngin {

class GameObject;

class GLNGIN_API Scene final {
public:
    static Scene &Instance();

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    void PreInit(int argc, char *argv[], const char *windowTitle, int windowWidth, int windowHeight);
    void Init();
    void Start() const;

    void AddGameObject(std::shared_ptr<GameObject> &&gameObject);
    void SetCamera(std::shared_ptr<Camera> _camera);
    void AddLight(Light &&_light);
    std::shared_ptr<GameObject> GetGameObject(const std::string &_id) const;

private:
    Scene() = default;

    friend void Draw();
    friend void Update();
    friend void Reshape(int newWidth, int newHeight);
    friend void Terminate();

private:
    std::unordered_map<std::string, std::shared_ptr<GameObject>> gameObjectMap;
    std::shared_ptr<Camera> camera;
    PerFrameData pfd;
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_SCENE_HPP
