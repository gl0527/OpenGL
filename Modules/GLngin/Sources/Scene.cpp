#include "Scene.hpp"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <IL/il.h>

#include "Debug.hpp"
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "Math.hpp"
#include "RenderState.hpp"
#include "Texture2D.hpp"
#include "TextureCube.hpp"

namespace GLngin {

void Draw()
{
    auto &scene = Scene::Instance();
    RenderState renderState;

    renderState.light = scene.light;
    if (scene.camera) {
        renderState.cameraPos = scene.camera->GetPosition();
        renderState.view = scene.camera->View();
        renderState.viewProj = scene.camera->View() * scene.camera->Proj();
    }

    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    for (const auto &[id, obj] : scene.gameObjectMap) {
        obj->Draw(renderState);
    }

    glutSwapBuffers();
}

void Update()
{
    auto &scene = Scene::Instance();

    static float tEnd = 0.0f;
    float tStart = tEnd;
    const float dt = 1e-2f;
    tEnd = glutGet(GLUT_ELAPSED_TIME) * 1e-3f;
    InputManager &input = InputManager::Instance();

    for (float t = tStart; t < tEnd; t += dt) {
        float Dt = Math::Min(dt, tEnd - tStart);
        scene.camera->Control(t, Dt, input);
        for (const auto &[id, obj] : scene.gameObjectMap) {
            obj->Control(t, Dt, input);
        }
        for (const auto &[id, obj] : scene.gameObjectMap) {
            obj->Animate(t, Dt);
        }
    }

    if (input.IsKeyReleased(InputManager::Key::ESCAPE)) {
        glutLeaveMainLoop();
        return;
    }

    input.Update();

    glutPostRedisplay();
}

void Reshape(int newWidth, int newHeight)
{
    auto &scene = Scene::Instance();

    GL_CALL(glViewport(0, 0, newWidth, newHeight));
    scene.camera->SetAspectRatio(newWidth, newHeight);
}

void Terminate()
{
    auto &scene = Scene::Instance();

    for (const auto &[id, obj] : scene.gameObjectMap) {
        obj->Terminate();
    }
    Texture2D::DeleteAll();
    TextureCube::DeleteAll();
}

Scene &Scene::Instance()
{
    static Scene instance;
    return instance;
}

void Scene::Init(int argc, char *argv[], const char *windowTitle, int windowWidth, int windowHeight)
{
    glutInit(&argc, argv);
    IL_CALL(ilInit());

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(windowTitle);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        std::cout << "Cannot initialize GLEW\n";
        exit(-1);
    }

    std::cout << GLngin::GetGLInfoString() << std::endl;

    GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GL_CALL(glEnable(GL_DEPTH_TEST));
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

    InputManager::Instance().Init();
    for (const auto &[id, obj] : gameObjectMap) {
        obj->Init();
    }

    glutDisplayFunc(Draw);
    glutIdleFunc(Update);
    glutReshapeFunc(Reshape);
    glutCloseFunc(Terminate);
}

void Scene::Start() const
{
    glutMainLoop();
}

void Scene::AddGameObject(std::shared_ptr<GameObject> &&gameObject)
{
    gameObjectMap.insert({gameObject->GetId(), gameObject});
}

void Scene::SetCamera(Camera &&_camera)
{
    camera = _camera;
}

void Scene::SetLigth(Light &&_light)
{
    light = _light;
}

std::shared_ptr<GameObject> Scene::GetGameObject(const std::string &_id) const
{
    for (const auto &[id, child] : gameObjectMap) {
        if (child->GetId() == _id) {
            return child->shared_from_this();
        }
    }
    return nullptr;
}

}  // namespace GLngin
