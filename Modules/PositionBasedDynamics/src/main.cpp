#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>

#include "Camera.hpp"
#include "Shader.hpp"
#include "Program.hpp"
#include "Debug.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "InputManager.hpp"
#include "Cube.hpp"
#include "TextureCube.hpp"


const unsigned int windowWidth = 600;
const unsigned int windowHeight = 600;

// Grid Resolution (resX=resY)
const unsigned int N = 64;
// Workgroup Size
const unsigned int Nwg = 32;
// Number of vertices (resX=resY)
const unsigned int vNum = N*N;

static GLngin::InputManager& inputManager = GLngin::InputManager::Instance ();

static GLngin::Camera camera (GLngin::Math::Vec3 (0, 0.5, 3), GLngin::Math::Vec3::NegativeUnitZ (), GLngin::Math::Vec3::UnitY ());
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


void onInitialization ()
{
    GL_CALL (glClearColor (0.1f, 0.1f, 0.1f, 1.0f));

    // Set point primitive size
    GL_CALL (glPointSize (8.0f));

    GL_CALL (glEnable (GL_BLEND));
    GL_CALL (glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    std::string currFolder (FOLDER);

    inputManager.Init ();

    skybox.Init ();
    skyboxTexture.Init ();
    skyboxTexture.Load (currFolder + "../assets/morning_rt.tga",
                        currFolder + "../assets/morning_lf.tga",
                        currFolder + "../assets/morning_up.tga",
                        currFolder + "../assets/morning_dn.tga",
                        currFolder + "../assets/morning_bk.tga",
                        currFolder + "../assets/morning_ft.tga");

    // initialize shaders
    GLngin::Shader gravityShader (GL_COMPUTE_SHADER);
    GLngin::Shader collisionShader (GL_COMPUTE_SHADER);
    GLngin::Shader distanceShader (GL_COMPUTE_SHADER);
    GLngin::Shader bendingShader (GL_COMPUTE_SHADER);
    GLngin::Shader finalUpdateShader (GL_COMPUTE_SHADER);
    GLngin::Shader vertexShader (GL_VERTEX_SHADER);
    GLngin::Shader fragmentShader (GL_FRAGMENT_SHADER);

    GLngin::Shader skyboxVertexShader (GL_VERTEX_SHADER);
    GLngin::Shader skyboxFragmentShader (GL_FRAGMENT_SHADER);

    gravityShader.Init (currFolder + "../shaders/gravity.comp");
    collisionShader.Init (currFolder + "../shaders/collision.comp");
    distanceShader.Init (currFolder + "../shaders/distance.comp");
    bendingShader.Init (currFolder + "../shaders/bending.comp");
    finalUpdateShader.Init (currFolder + "../shaders/finalUpdate.comp");
    vertexShader.Init (currFolder + "../shaders/render.vert");
    fragmentShader.Init (currFolder + "../shaders/render.frag");
    skyboxVertexShader.Init (currFolder + "../shaders/skybox.vert");
    skyboxFragmentShader.Init (currFolder + "../shaders/skybox.frag");

    // initialize programs
    gravityProgram.Init ();
    gravityProgram.AddShader (gravityShader);
    gravityProgram.Link ();

    collisionProgram.Init ();
    collisionProgram.AddShader (collisionShader);
    collisionProgram.Link ();

    distanceProgram.Init ();
    distanceProgram.AddShader (distanceShader);
    distanceProgram.Link ();

    bendingProgram.Init ();
    bendingProgram.AddShader (bendingShader);
    bendingProgram.Link ();

    finalUpdateProgram.Init ();
    finalUpdateProgram.AddShader (finalUpdateShader);
    finalUpdateProgram.Link ();

    renderProgram.Init ();
    renderProgram.AddShader (vertexShader);
    renderProgram.AddShader (fragmentShader);
    renderProgram.Link ();

    skyboxProgram.Init ();
    skyboxProgram.AddShader (skyboxVertexShader);
    skyboxProgram.AddShader (skyboxFragmentShader);
    skyboxProgram.Link ();

    // set up constant uniform variables
    const float dt = 0.002f;

    gravityProgram.Use ();
    if (!gravityProgram.SetUniformFloat ("dt", dt)) {
        LOG ("Cannot set \'dt\' as a float uniform variable.");
        exit (-1);
    }

    collisionProgram.Use ();
    if (!collisionProgram.SetUniformFloat ("ConstraintWeight", 0.1f)) {
        LOG ("Cannot set \'ConstraintWeight\' as a float uniform variable.");
        exit (-1);
    }

    distanceProgram.Use ();
    if (!distanceProgram.SetUniformFloat ("ConstraintWeight", 0.125f)) {
        LOG ("Cannot set \'ConstraintWeight\' as a float uniform variable.");
        exit (-1);
    }

    finalUpdateProgram.Use ();
    if (!finalUpdateProgram.SetUniformFloat ("dt", dt)) {
        LOG ("Cannot set \'dt\' as a float uniform variable.");
        exit (-1);
    }

    skyboxProgram.Use ();
    if (!skyboxProgram.SetUniformTextureCube ("cubeMap", skyboxTexture.GetID (), 0)) {
        LOG ("Cannot set \'cubeMap\' as a TextureCube uniform variable.");
        exit (-1);
    }

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
        pos[j*N+i] = GLngin::Math::Vec4 (static_cast<float> (i) / (N - 1.0f) - 0.5f, 0.0f, static_cast<float> (j) / (N - 1.0f) - 0.5f, 1.0f);
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
    GL_CALL (glBufferData (GL_SHADER_STORAGE_BUFFER, vNum * sizeof (GLngin::Math::Vec4), NULL, GL_STATIC_DRAW));

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

    GL_CALL (glEnableVertexAttribArray (0));
    GL_CALL (glBindBuffer (GL_ARRAY_BUFFER, positionBuffer));
    GL_CALL (glVertexAttribPointer (0, 4, GL_FLOAT, GL_FALSE, sizeof (GLngin::Math::Vec4), nullptr));

    GL_CALL (glBindVertexArray (0));
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

    // Render skybox
    skyboxProgram.Use ();
    GLngin::Math::Mat4 viewMat = camera.GetViewMatrix ().SetTranslation (GLngin::Math::Vec3::Zero ());

    if (!skyboxProgram.SetUniformMat4 ("viewProj", camera.GetProjMatrix () * viewMat)) {
        LOG ("Cannot set \'viewProj\' as a mat4 uniform variable.");
        exit (-1);
    }

    GL_CALL (glDepthMask (GL_FALSE));
    skybox.Render ();
    GL_CALL (glDepthMask (GL_TRUE));

    // Render the particles
    renderProgram.Use ();
    if (!renderProgram.SetUniformMat4 ("viewproj", camera.GetViewMatrix () * camera.GetProjMatrix ())) {
        LOG ("Cannot set \'viewproj\' as a mat4 uniform variable.");
        exit (-1);
    }

    GL_CALL (glBindVertexArray (vao));
    GL_CALL (glDrawArrays (GL_POINTS, 0, N*N));
    GL_CALL (glBindVertexArray (0));

    glutSwapBuffers ();
}


void onIdle ()
{
    float sec = glutGet (GLUT_ELAPSED_TIME) * 1e-3f;

    if (inputManager.IsKeyReleased (GLngin::InputManager::Key::ESCAPE)) {
        renderProgram.UnUse ();
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

    camera.Animate (sec);

    inputManager.Update ();

    glutPostRedisplay ();
}


int main (int argc, char* argv[])
{
    glutInit (&argc, argv);

    glutInitContextVersion (4, 3);
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
