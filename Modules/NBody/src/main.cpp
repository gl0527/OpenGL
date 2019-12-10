#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdio>
#include <cstring>

#include "Debug.hpp"
#include "InputManager.hpp"
#include "Math.hpp"
#include "Shader.hpp"
#include "Vec4.hpp"

constexpr unsigned int windowWidth = 600;
constexpr unsigned int windowHeight = 600;

constexpr unsigned int workgroupSize = 256;
constexpr unsigned int particlesNum = 1024;

static GLngin::Shader renderProgram;
static GLngin::Shader computeProgram;

static unsigned int ssboID;
static unsigned int vaoID;

static GLngin::InputManager &inputManager = GLngin::InputManager::Instance();

static void FillSSBO()
{
    GLngin::Math::Vec4 *ssboAddr = nullptr;
    GL_CALL(ssboAddr = static_cast<GLngin::Math::Vec4 *>(
                glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, particlesNum * sizeof(GLngin::Math::Vec4),
                                 GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)));

    // writing into the SSBO memory space
    for (unsigned int i = 0; i < particlesNum; ++i) {
        // 2D position
        ssboAddr[i].x = GLngin::Math::Random(-1.0f, 1.0f);
        ssboAddr[i].y = GLngin::Math::Random(-1.0f, 1.0f);
        // 2D velocity
        ssboAddr[i].z = GLngin::Math::Random(-1.0f, 1.0f);
        ssboAddr[i].w = GLngin::Math::Random(-1.0f, 1.0f);
    }

    GL_CALL(glUnmapBuffer(GL_SHADER_STORAGE_BUFFER));
}

static void onInitialization()
{
    inputManager.Init();

    GL_CALL(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));

    // Set point primitive size
    GL_CALL(glPointSize(4.0f));

    std::string currFolder(FOLDER);

    computeProgram.Init(std::nullopt, std::nullopt, std::nullopt, std::nullopt, std::nullopt,
                        currFolder + "../shaders/particle.comp");
    renderProgram.Init(currFolder + "../shaders/particle.vert", std::nullopt, std::nullopt, std::nullopt,
                       currFolder + "../shaders/particle.frag", std::nullopt);

    // Initialize the ssbo
    GL_CALL(glGenBuffers(1, &ssboID));
    GL_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboID));
    GL_CALL(glBufferData(GL_SHADER_STORAGE_BUFFER, particlesNum * sizeof(GLngin::Math::Vec4), nullptr, GL_STATIC_DRAW));

    FillSSBO();

    // Binding ssbo to the pipeline
    GL_CALL(glGenVertexArrays(1, &vaoID));
    GL_CALL(glBindVertexArray(vaoID));

    int vParticleDataIndex = renderProgram.GetAttributeLocation("vParticleData");
    GL_CALL(glEnableVertexAttribArray(vParticleDataIndex));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, ssboID));
    GL_CALL(glVertexAttribPointer(vParticleDataIndex, 4, GL_FLOAT, GL_FALSE, 0, nullptr));

    GL_CALL(glBindVertexArray(0));
}

static void onDisplay()
{
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    // Update position and velocity
    GL_CALL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssboID));

    computeProgram.Bind();
    GL_CALL(glDispatchCompute(particlesNum / workgroupSize, 1, 1));

    // Synchronize between the compute and render shaders
    GL_CALL(glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT));

    // Render the particles
    renderProgram.Bind();
    GL_CALL(glBindVertexArray(vaoID));
    GL_CALL(glDrawArrays(GL_POINTS, 0, particlesNum));
    GL_CALL(glBindVertexArray(0));

    glutSwapBuffers();
}

static void onIdle()
{
    if (inputManager.IsKeyPressed(GLngin::InputManager::Key::ESCAPE)) {
        computeProgram.UnBind();
        renderProgram.UnBind();

        GL_CALL(glDeleteBuffers(1, &ssboID));
        GL_CALL(glDeleteVertexArrays(1, &vaoID));

        exit(0);
    }

    if (inputManager.IsKeyReleased(GLngin::InputManager::Key::R) ||
        inputManager.IsKeyDown(GLngin::InputManager::Key::r)) {
        FillSSBO();
    }

    if (inputManager.IsRightMouseButtonDown())
        glutFullScreen();
    else
        glutLeaveFullScreen();

    if (inputManager.IsLeftMouseButtonDown()) inputManager.Disable();

    inputManager.Update();

    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int>(time(nullptr)));

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
    glutIdleFunc(onIdle);

    glutMainLoop();

    return 0;
}
