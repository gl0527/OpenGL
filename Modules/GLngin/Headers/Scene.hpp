#pragma once

#ifndef GLNGIN_SCENE_HPP
#define GLNGIN_SCENE_HPP

#include <unordered_map>
#include <memory>
#include <optional>
#include "API.hpp"
#include "Camera.hpp"
#include "Light.hpp"


namespace GLngin {

class GameObject;

class GLNGIN_API Scene {
public:
    static Scene &Instance();

    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    void Init(int argc, char *argv[], const char *windowTitle, int windowWidth,
          int windowHeight);
    void Start() const;

    void AddGameObject(std::shared_ptr<GameObject> &&gameObject);
    void SetCamera(Camera &&_camera);
    void SetLigth(Light &&_light);
    std::shared_ptr<GameObject> GetGameObject(const std::string &_id) const;

private:
    Scene() = default;

    friend void Draw();
    friend void Update();
    friend void Reshape(int newWidth, int newHeight);
    friend void Terminate();

private:
    std::unordered_map<std::string, std::shared_ptr<GameObject>> gameObjectMap;
    std::optional<Camera> camera;
    std::optional<Light> light;
};

}  // namespace GLngin

#endif  // #ifndef GLNGIN_SCENE_HPP
