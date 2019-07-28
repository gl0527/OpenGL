#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>
#include <cstring>

#include "Camera.hpp"
#include "Program.hpp"
#include "Debug.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "InputManager.hpp"
#include "Cube.hpp"
#include "TextureCube.hpp"
#include "Timer.hpp"
#include "Ball.hpp"


const unsigned int windowWidth = 600;
const unsigned int windowHeight = 600;

// Grid Resolution (resX=resY)
const unsigned int N = 64;
// Workgroup Size
const unsigned int Nwg = 32;
// Number of vertices (resX=resY)
const unsigned int vNum = N*N;

static GLngin::Timer timer;

static GLngin::InputManager& inputManager = GLngin::InputManager::Instance ();

static GLngin::Camera camera (GLngin::Math::Vec3 (0, 1, -3.0), GLngin::Math::Vec3 (0,0,0), GLngin::Math::Vec3::UnitY ());
static GLngin::Cube skybox;
static GLngin::TextureCube skyboxTexture;

//compute shaders
static GLngin::Program gravityProgram;
static GLngin::Program collisionProgram;
static GLngin::Program distanceProgram;
static GLngin::Program bendingProgram;
static GLngin::Program finalUpdateProgram;
//standard pipeline
static GLngin::Program renderProgram;
static GLngin::Program skyboxProgram;

// Position buffer
static GLuint positionBuffer; //x
static GLuint positionBufferTmp; //p
static GLuint velocityBuffer; //v

// Vertex array object
static GLuint vao;

Ball ball ("Ball", GLngin::Math::Vec3 (0.0f, -0.25f, 0.0f));


void onInitialization ()
{
    GL_CALL (glClearColor (0.1f, 0.1f, 0.1f, 1.0f));

    // Set point primitive size
    GL_CALL (glPointSize (4.0f));
    GL_CALL (glEnable (GL_POINT_SMOOTH));

    GL_CALL (glEnable (GL_BLEND));
    GL_CALL (glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    GL_CALL (glEnable (GL_DEPTH_TEST));

    std::string currFolder (FOLDER);

    inputManager.Init ();

    skybox.Init (500);
    skyboxTexture.Init ();
    skyboxTexture.Load (currFolder + "../assets/emerald_rt.tga",
                        currFolder + "../assets/emerald_lf.tga",
                        currFolder + "../assets/emerald_up.tga",
                        currFolder + "../assets/emerald_dn.tga",
                        currFolder + "../assets/emerald_bk.tga",
                        currFolder + "../assets/emerald_ft.tga");

    // initialize programs
    gravityProgram.Init ();
    gravityProgram.AddShaderFromFile (GL_COMPUTE_SHADER, currFolder + "../shaders/gravity.comp");
    gravityProgram.Link ();

    collisionProgram.Init ();
    collisionProgram.AddShaderFromFile (GL_COMPUTE_SHADER, currFolder + "../shaders/collision.comp");
    collisionProgram.Link ();

    distanceProgram.Init ();
    distanceProgram.AddShaderFromFile (GL_COMPUTE_SHADER, currFolder + "../shaders/distance.comp");
    distanceProgram.Link ();

    bendingProgram.Init ();
    bendingProgram.AddShaderFromFile (GL_COMPUTE_SHADER, currFolder + "../shaders/bending.comp");
    bendingProgram.Link ();

    finalUpdateProgram.Init ();
    finalUpdateProgram.AddShaderFromFile (GL_COMPUTE_SHADER, currFolder + "../shaders/finalUpdate.comp");
    finalUpdateProgram.Link ();

    renderProgram.Init ();
    renderProgram.AddShaderFromFile (GL_VERTEX_SHADER, currFolder + "../shaders/render.vert");
    renderProgram.AddShaderFromFile (GL_FRAGMENT_SHADER, currFolder + "../shaders/render.frag");
    renderProgram.Link ();

    skyboxProgram.Init ();
    skyboxProgram.AddShaderFromFile (GL_VERTEX_SHADER, currFolder + "../shaders/skybox.vert");
    skyboxProgram.AddShaderFromFile (GL_FRAGMENT_SHADER, currFolder + "../shaders/skybox.frag");
    skyboxProgram.Link ();

    // set up constant uniform variables
    const float dt = 0.0015f;

    gravityProgram.Use ();
    gravityProgram.SetUniformFloat ("dt", dt);

    collisionProgram.Use ();
    collisionProgram.SetUniformFloat ("ConstraintWeight", 0.9f);

    distanceProgram.Use ();
    distanceProgram.SetUniformFloat ("ConstraintWeight", 0.25f);

    finalUpdateProgram.Use ();
    finalUpdateProgram.SetUniformFloat ("dt", dt);

    skyboxProgram.Use ();
    skyboxProgram.SetUniformTextureCube ("cubeMap", skyboxTexture.GetID (), 0);

    // Initialize the particle position buffer
    GL_CALL (glGenBuffers (1, &positionBuffer));
    GL_CALL (glBindBuffer (GL_SHADER_STORAGE_BUFFER, positionBuffer));
    GL_CALL (glBufferData (GL_SHADER_STORAGE_BUFFER, vNum * sizeof (GLngin::Math::Vec4), nullptr, GL_STATIC_DRAW));

    GLngin::Math::Vec4 * pos = nullptr;
    GL_CALL (pos = static_cast<GLngin::Math::Vec4*> (glMapBufferRange (GL_SHADER_STORAGE_BUFFER,
                                                                      0,
                                                                      vNum * sizeof (GLngin::Math::Vec4),
                                                                      GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)));
    for (unsigned int i = 0; i < N; ++i)
        for (unsigned int j = 0; j < N; ++j)
        {
            pos[i*N+j] = GLngin::Math::Vec4 (i / (N - 1.0f) - 0.5f, 0.5f, j / (N - 1.0f) - 0.5f, 1.0f);
        }
    GL_CALL (glUnmapBuffer (GL_SHADER_STORAGE_BUFFER));

    GL_CALL (glGenBuffers (1, &positionBufferTmp));
    GL_CALL (glBindBuffer (GL_SHADER_STORAGE_BUFFER, positionBufferTmp));
    GL_CALL (glBufferData (GL_SHADER_STORAGE_BUFFER, vNum * sizeof (GLngin::Math::Vec4), nullptr, GL_STATIC_DRAW));

    GL_CALL (glMapBufferRange (GL_SHADER_STORAGE_BUFFER,
                              0,
                              vNum * sizeof (GLngin::Math::Vec4),
                              GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
    GL_CALL (glUnmapBuffer (GL_SHADER_STORAGE_BUFFER));

    GL_CALL (glGenBuffers (1, &velocityBuffer));
    GL_CALL (glBindBuffer (GL_SHADER_STORAGE_BUFFER, velocityBuffer));
    GL_CALL (glBufferData (GL_SHADER_STORAGE_BUFFER, vNum * sizeof (GLngin::Math::Vec4), nullptr, GL_STATIC_DRAW));

    GLngin::Math::Vec4 * vel = nullptr;
    GL_CALL (vel = static_cast<GLngin::Math::Vec4*> (glMapBufferRange (GL_SHADER_STORAGE_BUFFER, 0, vNum * sizeof (GLngin::Math::Vec4), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)));
    for (unsigned int i = 0; i < vNum; ++i) {
        vel[i] = GLngin::Math::Vec4 ();
    }
    GL_CALL (glUnmapBuffer (GL_SHADER_STORAGE_BUFFER));

    GL_CALL (glBindBuffer (GL_SHADER_STORAGE_BUFFER, 0));

    // Initialize the vertex array object with the position buffer
    GL_CALL (glGenVertexArrays (1, &vao));
    GL_CALL (glBindVertexArray (vao));

    int vPositionIndex = renderProgram.GetAttributeIndex ("vPosition");
    GL_CALL (glEnableVertexAttribArray (vPositionIndex));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, positionBuffer));
    GL_CALL (glVertexAttribPointer (vPositionIndex, 4, GL_FLOAT, GL_FALSE, sizeof (GLngin::Math::Vec4), nullptr));

    GL_CALL (glBindVertexArray (0));

    ball.Init ();
}


void onDisplay ()
{
    GL_CALL (glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    GL_CALL (glBindBufferBase (GL_SHADER_STORAGE_BUFFER, 0, positionBuffer));
    GL_CALL (glBindBufferBase (GL_SHADER_STORAGE_BUFFER, 1, positionBufferTmp));
    GL_CALL (glBindBufferBase (GL_SHADER_STORAGE_BUFFER, 2, velocityBuffer));

    gravityProgram.Use ();
    GL_CALL (glDispatchCompute (N/Nwg, N/Nwg, 1));
    GL_CALL (glMemoryBarrier (GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));

    const int NITER = 50;
    for (int i = 0; i < NITER; ++i) {
        collisionProgram.Use ();
        GL_CALL (glDispatchCompute (N/Nwg, N/Nwg, 1));
        GL_CALL (glMemoryBarrier (GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));

        distanceProgram.Use ();
        GL_CALL (glDispatchCompute (N/Nwg, N/Nwg, 1));
        GL_CALL (glMemoryBarrier (GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));
    }

    finalUpdateProgram.Use ();
    GL_CALL (glDispatchCompute (N/Nwg, N/Nwg, 1));
    GL_CALL (glMemoryBarrier (GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));

    GLngin::Math::Mat4 VP = camera.View () * camera.Proj ();

    // Render skybox
    skyboxProgram.Use ();
    skyboxProgram.SetUniformMat4 ("MVP", VP);
    skybox.Render ();

    // Render the particles
    renderProgram.Use ();
    renderProgram.SetUniformMat4 ("MVP", GLngin::Math::Mat4::Translate (GLngin::Math::Vec3 (0,1,0)) * VP);
    GL_CALL (glBindVertexArray (vao));
    GL_CALL (glDrawArrays (GL_POINTS, 0, N*N));
    GL_CALL (glBindVertexArray (0));

    ball.Draw (&camera);

    glutSwapBuffers ();
}


void onIdle ()
{
    timer.Tick ();
    const float dt = timer.GetDeltaTime ();

    if (inputManager.IsKeyReleased (GLngin::InputManager::Key::ESCAPE)) {
        renderProgram.UnUse ();
        skyboxProgram.UnUse ();
        finalUpdateProgram.UnUse ();
        bendingProgram.UnUse ();
        distanceProgram.UnUse ();
        collisionProgram.UnUse ();
        gravityProgram.UnUse ();

        GL_CALL (glDeleteBuffers (1, &velocityBuffer));
        GL_CALL (glDeleteBuffers (1, &positionBufferTmp));
        GL_CALL (glDeleteBuffers (1, &positionBuffer));
        GL_CALL (glDeleteVertexArrays (1, &vao));

        exit (0);
    }

    camera.Animate (dt);
    inputManager.Update ();

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
    glGetError ();

    std::cout << GLngin::GetGLInfoString () << std::endl;

    onInitialization ();
    glutDisplayFunc (onDisplay);
    glutIdleFunc (onIdle);

    glutMainLoop ();

    return 0;
}
