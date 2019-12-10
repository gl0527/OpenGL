#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>
#include <cstring>

#include "Shader.hpp"
#include "Debug.hpp"
#include "Quad.hpp"

constexpr unsigned int windowWidth = 600;
constexpr unsigned int windowHeight = 600;

static GLngin::Quad quad;
static GLngin::Shader program;

static void onInitialization()
{
    glClearColor(0.4f, 0.6f, 0.8f, 1.0f);

    std::string currFolder(FOLDER);

    quad.Init();

    program.Init(currFolder + "../shaders/passthrough.vert", std::nullopt, std::nullopt, std::nullopt,
                 currFolder + "../shaders/simple.frag", std::nullopt);
    program.Bind();
}

static void onDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    quad.Render();

    glutSwapBuffers();
}

static void onKeyboard(unsigned char key, int /*pX*/, int /*pY*/)
{
    switch (key) {
        case 27: program.UnBind(); exit(0);

        default: break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitContextVersion(3, 3);
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
    glutKeyboardFunc(onKeyboard);
    glutMainLoop();

    return 0;
}
