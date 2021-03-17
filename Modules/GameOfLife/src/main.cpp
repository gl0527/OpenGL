#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>
#include <cstring>
#include <cassert>

#include <IL/il.h>

#include "Debug.hpp"
#include "Shader.hpp"
#include "Quad.hpp"
#include "FrameBuffer.hpp"

static GLngin::Quad quad;
static GLngin::Shader render, calc;
static GLngin::FrameBuffer fbo[2];

static void onInitialization(char const *const imgPath)
{
    std::string currFolder(FOLDER);

    quad.Init();

    std::string vs;
    if (auto vsOpt = GLngin::GetFileContent(currFolder + "../shaders/gol.vert")) {
        vs = vsOpt.value();
    } else {
        LOG("Error occurred during file reading!");
        return;
    }

    std::string fsCalc;
    if (auto fsOpt = GLngin::GetFileContent(currFolder + "../shaders/gol.frag")) {
        fsCalc = fsOpt.value();
    } else {
        LOG("Error occurred during file reading!");
        return;
    }

    std::string fsRender;
    if (auto fsOpt = GLngin::GetFileContent(currFolder + "../shaders/render.frag")) {
        fsRender = fsOpt.value();
    } else {
        LOG("Error occurred during file reading!");
        return;
    }

    calc.Init(vs, std::nullopt, std::nullopt, std::nullopt, fsCalc, std::nullopt);
    render.Init(vs, std::nullopt, std::nullopt, std::nullopt, fsRender, std::nullopt);

    fbo[0].Create(imgPath);
    fbo[1].Create(imgPath);

    glutReshapeWindow(fbo[0].GetWidth(), fbo[0].GetHeight());
}

static void onDisplay()
{
    static unsigned char dst = 0;
    unsigned char src = 1 - dst;

    fbo[dst].Bind();
    calc.Bind();
    calc.SetUniformTexture2D("tex", fbo[src].GetColorAttachmentID(), 0);
    quad.Render();
    calc.UnBind();
    fbo[dst].UnBind();

    render.Bind();
    render.SetUniformTexture2D("tex", fbo[src].GetColorAttachmentID(), 0);
    quad.Render();
    render.UnBind();

    dst = src;

    glFlush();
}

static void onIdle()
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    assert(argc == 2);

    glutInit(&argc, argv);
    IL_CALL(ilInit());

    glutInitContextVersion(3, 3);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutCreateWindow(argv[0]);
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Cannot initialize GLEW\n");
        exit(-1);
    }

    std::cout << GLngin::GetGLInfoString() << std::endl;

    onInitialization(argv[1]);

    glutDisplayFunc(onDisplay);
    glutIdleFunc(onIdle);

    glutMainLoop();

    return 0;
}
