#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>

#include "Shader.hpp"
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
    glClearColor (0.4f, 0.6f, 0.8f, 1.0f);

    std::string currFolder (FOLDER);

    quad.Init ();

    GLngin::Shader vertexShader (GL_VERTEX_SHADER);
    GLngin::Shader fragmentShader (GL_FRAGMENT_SHADER);

    vertexShader.Init (currFolder + "../shaders/ImageProcessing.vert");
    fragmentShader.Init (currFolder + "../shaders/ImageProcessing.frag");

    program.Init ();
    program.AddShader (vertexShader);
    program.AddShader (fragmentShader);
    program.Link ();
    program.Use ();

    tex.Init ();
    tex.Load (currFolder + "../assets/lena.jpg");

    if (!program.SetUniformTexture2D ("tex", tex.GetID (), 0))
        LOG ("Texture setting error");
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
            program.UnUse ();
            exit (0);

        default: break;
    }
}


int main (int argc, char* argv[])
{
    glutInit (&argc, argv);

    glutInitContextVersion (3, 3);
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
