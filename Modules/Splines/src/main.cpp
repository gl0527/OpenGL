#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>

#include "Shader.hpp"
#include "Program.hpp"
#include "Debug.hpp"
#include "InputManager.hpp"


constexpr unsigned int windowWidth = 600;
constexpr unsigned int windowHeight = 600;

static GLngin::Program program;
static GLngin::InputManager& input = GLngin::InputManager::Instance ();

static unsigned int vao;
static unsigned int vbo;

static unsigned char idx = 0;


static void onInitialization ()
{
    GL_CALL (glClearColor (0.2f, 0.2f, 0.2f, 0.2f));

    input.Init ();

    std::string currFolder (FOLDER);

    GLngin::Shader vertexShader (GL_VERTEX_SHADER);
    GLngin::Shader geometryShader (GL_GEOMETRY_SHADER);
    GLngin::Shader fragmentShader (GL_FRAGMENT_SHADER);

    vertexShader.LoadFromFile (currFolder + "../shaders/Splines.vert");
    geometryShader.LoadFromFile (currFolder + "../shaders/Splines.geom");
    fragmentShader.LoadFromFile (currFolder + "../shaders/Splines.frag");

    program.Init ();
    program.AddShader (vertexShader);
    program.AddShader (geometryShader);
    program.AddShader (fragmentShader);
    program.Link ();

    GL_CALL (glGenBuffers (1, &vbo));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, vbo));
    GL_CALL (glBufferData (GL_ARRAY_BUFFER, 20 * sizeof (float), nullptr, GL_STATIC_DRAW));

    GL_CALL (glGenVertexArrays (1, &vao));
    GL_CALL (glBindVertexArray (vao));

    GL_CALL (glEnableVertexAttribArray (0));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, vbo));
    GL_CALL (glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 0, nullptr));

    GL_CALL (glBindVertexArray (0));

    program.Use ();
}


static void onDisplay ()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GL_CALL (glBindVertexArray (vao));
    GL_CALL (glDrawArrays (GL_LINE_STRIP_ADJACENCY, 0, idx / 2));
    GL_CALL (glBindVertexArray (0));

    glutSwapBuffers ();
}


static void onIdle ()
{
    if (input.IsKeyReleased (GLngin::InputManager::Key::SPACE) && idx < 19) {
        float ndcX, ndcY;
        input.GetMouseCoordsInNDC (&ndcX, &ndcY);

        float arr[] = { ndcX, ndcY };

        GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, vbo));
        GL_CALL (glBufferSubData (GL_ARRAY_BUFFER, idx * sizeof (float), sizeof (arr), arr));
        GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, 0));

        idx += 2;
    }

    if (input.IsKeyPressed (GLngin::InputManager::Key::ESCAPE)) {
        program.UnUse ();

        GL_CALL (glDeleteBuffers (1, &vbo));
        GL_CALL (glDeleteVertexArrays (1, &vao));

        exit (0);
    }

    input.Update ();

    glutPostRedisplay ();
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
    glutIdleFunc (onIdle);
    glutMainLoop ();

    return 0;
}
