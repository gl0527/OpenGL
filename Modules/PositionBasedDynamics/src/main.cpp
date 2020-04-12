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


int main(int argc, char *argv[])
{
    const std::string currFolder(FOLDER);

    auto &scene = GLngin::Scene::Instance();

    scene.SetCamera({GLngin::Math::Vec3(0, 1, -3.0), GLngin::Math::Vec3(0, 0, 0), GLngin::Math::Vec3::UnitY(), 1, 1});

    scene.AddGameObject(std::make_shared<Background>(   "bg",
                                                        currFolder + "../assets/morning_rt.tga",
                                                        currFolder + "../assets/morning_lf.tga",
                                                        currFolder + "../assets/morning_up.tga",
                                                        currFolder + "../assets/morning_dn.tga",
                                                        currFolder + "../assets/morning_bk.tga",
                                                        currFolder + "../assets/morning_ft.tga"));

    for (int i = 0; i < 100; ++i) {
        scene.AddGameObject(
            std::make_shared<Ball>("ball" + std::to_string(i), GLngin::Math::Vec3(i % 5, i / 5, i / 5)));
    }

    scene.AddGameObject(std::make_shared<Cloth>("cloth", GLngin::Math::Vec3(0, 2, 0)));
    scene.Init(argc, argv, "Cloth simulation", 800, 600);
    scene.Start();
    return 0;
}
