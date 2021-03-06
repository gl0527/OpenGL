#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>
#include <cstring>

#include "Shader.hpp"
#include "Debug.hpp"
#include "InputManager.hpp"
#include "Vec2.hpp"

constexpr unsigned int windowWidth = 600;
constexpr unsigned int windowHeight = 600;

static GLngin::Shader program;
static GLngin::InputManager &input = GLngin::InputManager::Instance();

static unsigned int vao;
static unsigned int vbo;

static unsigned char idx = 0;

static void onInitialization()
{
    GL_CALL(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

    input.Init();

    std::string currFolder(FOLDER);

    std::string vs;
    if (auto vsOpt = GLngin::GetFileContent(currFolder + "../shaders/Splines.vert")) {
        vs = vsOpt.value();
    } else {
        LOG("Error occurred during file reading!");
        return;
    }

    std::string gs;
    if (auto gsOpt = GLngin::GetFileContent(currFolder + "../shaders/Splines.geom")) {
        gs = gsOpt.value();
    } else {
        LOG("Error occurred during file reading!");
        return;
    }

    std::string fs;
    if (auto fsOpt = GLngin::GetFileContent(currFolder + "../shaders/Splines.frag")) {
        fs = fsOpt.value();
    } else {
        LOG("Error occurred during file reading!");
        return;
    }

    program.Init(vs, gs, std::nullopt, std::nullopt, fs, std::nullopt);

    GL_CALL(glGenBuffers(1, &vbo));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CALL(glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), nullptr, GL_STATIC_DRAW));

    GL_CALL(glGenVertexArrays(1, &vao));
    GL_CALL(glBindVertexArray(vao));

    int vDataIndex = program.GetAttributeLocation("vData");
    GL_CALL(glEnableVertexAttribArray(vDataIndex));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
    GL_CALL(glVertexAttribPointer(vDataIndex, 2, GL_FLOAT, GL_FALSE, 0, nullptr));

    GL_CALL(glBindVertexArray(0));

    program.Bind();
}

static void onDisplay()
{
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CALL(glBindVertexArray(vao));
    GL_CALL(glDrawArrays(GL_LINE_STRIP_ADJACENCY, 0, idx / 2));
    GL_CALL(glBindVertexArray(0));

    glutSwapBuffers();
}

static void onIdle()
{
    if (input.IsKeyReleased(GLngin::InputManager::Key::SPACE) && idx < 19) {
        GLngin::Math::Vec2 ndc = input.GetMouseCoordsInNDC();
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
        GL_CALL(glBufferSubData(GL_ARRAY_BUFFER, idx * sizeof(float), sizeof(ndc), &ndc));
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

        idx += 2;
    }

    if (input.IsKeyPressed(GLngin::InputManager::Key::ESCAPE)) {
        program.UnBind();

        GL_CALL(glDeleteBuffers(1, &vbo));
        GL_CALL(glDeleteVertexArrays(1, &vao));

        exit(0);
    }

    input.Update();

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow(argv[0]);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Cannot initialize GLEW\n");
        exit(-1);
    }

    std::cout << GLngin::GetGLInfoString() << std::endl;

    onInitialization();
    glutDisplayFunc(onDisplay);
    glutIdleFunc(onIdle);
    glutMainLoop();

    return 0;
}
