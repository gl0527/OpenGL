#include "Shader.hpp"
#include "Program.hpp"
#include "Debug.hpp"
#include "Math.hpp"
#include "Vec4.hpp"

#include <GL/freeglut.h>


constexpr unsigned int windowWidth = 600;
constexpr unsigned int windowHeight = 600;

constexpr unsigned int workgroupSize = 256;
constexpr unsigned int particlesNum = 1024;

static GLngin::Program renderProgram;
static GLngin::Program computeProgram;

static unsigned int ssbo;
static unsigned int vao;


static void FillSSBO ()
{
    GLngin::Math::Vec4 * ssboAddr = nullptr;
    GL_CALL (ssboAddr = static_cast<GLngin::Math::Vec4*> (glMapBufferRange (
                                                         GL_SHADER_STORAGE_BUFFER,
                                                         0,
                                                         particlesNum * sizeof (GLngin::Math::Vec4),
                                                         GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)));

    // writing into the SSBO memory space
    for (unsigned int i = 0; i < particlesNum; ++i) {
        // 2D position
        ssboAddr[i].x = GLngin::Math::Random (-1.0f, 1.0f);
        ssboAddr[i].y = GLngin::Math::Random (-1.0f, 1.0f);
        // 2D velocity
        ssboAddr[i].z = GLngin::Math::Random (-1.0f, 1.0f);
        ssboAddr[i].w = GLngin::Math::Random (-1.0f, 1.0f);
    }

    GL_CALL (glUnmapBuffer (GL_SHADER_STORAGE_BUFFER));
}


static void onInitialization ()
{
    GL_CALL (glClearColor (0.1f, 0.1f, 0.1f, 1.0f));

    // Set point primitive size
    GL_CALL (glPointSize (4.0f));

    std::shared_ptr<GLngin::Shader> pVs (new GLngin::Shader (GL_VERTEX_SHADER));
    std::shared_ptr<GLngin::Shader> pFs (new GLngin::Shader (GL_FRAGMENT_SHADER));
    std::shared_ptr<GLngin::Shader> pCs (new GLngin::Shader (GL_COMPUTE_SHADER));

    pVs->Init ("/home/lui/dev/cpp/gfx/Modules/NBody/shaders/particle.vert");
    pFs->Init ("/home/lui/dev/cpp/gfx/Modules/NBody/shaders/particle.frag");
    pCs->Init ("/home/lui/dev/cpp/gfx/Modules/NBody/shaders/particle.comp");

    // TODO a shadereket nem kene a heap-en foglalni
    // TODO minden shader tipusbol lehet egyszerre tobb is egy adott programhoz csatolva, ez jelenleg nem megoldhato
    // TODO tesszellacios shadereket sem lehet a jelenlegi modellben abrazolni
    computeProgram.Init (nullptr, nullptr, nullptr, pCs);
    computeProgram.Link ();
    renderProgram.Init (pVs, pFs, nullptr, nullptr);
    renderProgram.Link ();

    // Initialize the ssbo
    GL_CALL (glGenBuffers (1, &ssbo));
    GL_CALL (glBindBuffer (GL_SHADER_STORAGE_BUFFER, ssbo));
    GL_CALL (glBufferData (GL_SHADER_STORAGE_BUFFER, particlesNum * sizeof (GLngin::Math::Vec4), nullptr, GL_STATIC_DRAW));

    FillSSBO ();

    // Binding ssbo to the pipeline
    GL_CALL (glGenVertexArrays (1, &vao));
    GL_CALL (glBindVertexArray (vao));

    GL_CALL (glEnableVertexAttribArray (0));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, ssbo));
    GL_CALL (glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, 0, nullptr));

    GL_CALL (glBindVertexArray (0));
}


static void onDisplay ()
{
    GL_CALL (glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    // Update position and velocity
    GL_CALL (glBindBufferBase (GL_SHADER_STORAGE_BUFFER, 0, ssbo));

    computeProgram.Enable ();
    GL_CALL (glDispatchCompute (particlesNum / workgroupSize, 1, 1));
    computeProgram.Disable ();

    // Synchronize between the compute and render shaders
    GL_CALL (glMemoryBarrier (GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));

    // Render the particles
    renderProgram.Enable ();
    GL_CALL (glBindVertexArray (vao));
    GL_CALL (glDrawArrays (GL_POINTS, 0, particlesNum));
    GL_CALL (glBindVertexArray (0));
    renderProgram.Disable ();

    glutSwapBuffers ();
}


static void onKeyboard (unsigned char key, int /*pX*/, int /*pY*/)
{
    switch (key) {
        case 27:
            computeProgram.Disable ();
            renderProgram.Disable ();

            GL_CALL (glDeleteBuffers (1, &ssbo));
            GL_CALL (glDeleteVertexArrays (1, &vao));

            exit (0);

        case 'R':
        case 'r':
            FillSSBO ();
        break;

        default:
            break;
    }
}


static void onIdle ()
{
    glutPostRedisplay ();
}


int main (int argc, char* argv[])
{
    srand (static_cast<unsigned int> (time (nullptr)));

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
    glutIdleFunc (onIdle);
    glutMainLoop ();

    return 0;
}
