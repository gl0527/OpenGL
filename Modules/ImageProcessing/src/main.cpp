#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>
#include <cstring>

#include "Program.hpp"
#include "Debug.hpp"
#include "Quad.hpp"
#include "Texture2D.hpp"


constexpr unsigned int windowWidth = 600;
constexpr unsigned int windowHeight = 600;

static GLngin::Quad quad;
static GLngin::Program program;
static GLngin::Texture2D tex;


static void onInitialization ()
{
    GL_CALL (glClearColor (0.0f, 0.0f, 0.0f, 0.0f));

    std::string currFolder (FOLDER);

    quad.Init ();

    tex.Init ();
    tex.Load (currFolder + "../assets/lena.jpg");

    program.Init (currFolder + "../shaders/ImageProcessing.vert", std::nullopt, std::nullopt, std::nullopt, currFolder + "../shaders/ImageProcessing.frag", std::nullopt);
    program.Bind ();
    program.SetUniformTexture2D ("tex", tex.GetID (), 0);
}


static void onDisplay ()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    quad.Render ();
    glutSwapBuffers ();
}


static void onKeyboard (unsigned char key, int /*pX*/, int /*pY*/)
{
    switch (key) {
        case 27:
            program.UnBind ();
            exit (0);

        default: break;
    }
}


int main (int argc, char* argv[])
{
    glutInit (&argc, argv);

    glutInitWindowSize (windowWidth, windowHeight);
    glutInitWindowPosition (100, 100);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow (argv[0]);
    glewExperimental = true;
    if (glewInit () != GLEW_OK) {
        printf ("Cannot initialize GLEW\n");
        exit (-1);
    }

    std::cout << GLngin::GetGLInfoString () << std::endl;

    onInitialization ();
    glutDisplayFunc (onDisplay);
    glutKeyboardFunc (onKeyboard);
    glutMainLoop ();

    return 0;
}
