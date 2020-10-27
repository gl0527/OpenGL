#include "Scene.hpp"

#include "Camera.hpp"
#include "Ball.hpp"
#include "Background.hpp"
#include "Cloth.hpp"
#include <memory>

#include "Debug.hpp"
#include <GL/glew.h>
#include <cstdio>
#include <cstring>
#include "Material/Gold.hpp"
#include "Material/Skybox.hpp"

int main(int argc, char *argv[])
{
    const std::string currFolder(FOLDER);
    auto &scene = GLngin::Scene::Instance();
    scene.PreInit(argc, argv, 800, 600);

    std::string names[6] = {currFolder + "../assets/morning_rt.tga", currFolder + "../assets/morning_lf.tga",
                            currFolder + "../assets/morning_up.tga", currFolder + "../assets/morning_dn.tga",
                            currFolder + "../assets/morning_bk.tga", currFolder + "../assets/morning_ft.tga"};

    const std::shared_ptr<GLngin::Material::Material> gold(new GLngin::Material::Gold(names));
    const std::shared_ptr<GLngin::Material::Material> skybox(new GLngin::Material::Skybox(names));

    scene.SetAmbientLight(GLngin::Math::Vec3(0.1f, 0.1f, 0.1f));

    std::shared_ptr<GLngin::Camera> cam(new GLngin::Camera(GLngin::Math::Vec3(0, 1, -3.0), GLngin::Math::Vec3(0, 0, 0),
                                                           GLngin::Math::Vec3::UnitY(), 1, 1));
    scene.SetCamera(cam);

    scene.AddGameObject(std::make_shared<Background>("bg", skybox, names));

    for (int i = 0; i < 100; ++i) {
        scene.AddGameObject(
            std::make_shared<Ball>("ball" + std::to_string(i), gold, GLngin::Math::Vec3(i % 5, i / 5, i / 5)));
    }

    // scene.AddGameObject(std::make_shared<Cloth>("cloth", GLngin::Math::Vec3(0, 2, 0)));

    scene.Init();
    scene.Start();
    return 0;
}
