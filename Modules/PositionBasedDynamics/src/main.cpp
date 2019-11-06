#include "Scene.hpp"

#include "Camera.hpp"
#include "Ball.hpp"
#include "Cloth.hpp"
#include <memory>


int main (int argc, char* argv[])
{
    auto& scene = GLngin::Scene::Instance ();

    scene.SetCamera ({GLngin::Math::Vec3 (0, 1, -3.0), GLngin::Math::Vec3 (0,0,0), GLngin::Math::Vec3::UnitY (), 1, 1});

    for (int i = 0; i < 100; ++i) {
        scene.AddGameObject (std::make_shared<Ball> ("ball" + std::to_string (i), GLngin::Math::Vec3 (i % 5 , i / 5, i / 5)));
    }

    scene.AddGameObject (std::make_shared<Cloth> ("cloth", GLngin::Math::Vec3 (0,2,0)));
    scene.Init (argc, argv, "Cloth simulation", 800, 600);
    scene.Start ();
}
