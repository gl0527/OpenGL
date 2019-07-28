#include "Ball.hpp"

#include "Debug.hpp"
#include "Mat4.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include <GL/glew.h>
#include <cstdio>
#include <cstring>


void Ball::InitImpl ()
{
    std::string currFolder (FOLDER);

    program.Init ();
    program.AddShaderFromFile (GL_VERTEX_SHADER, currFolder + "../shaders/ball.vert");
    program.AddShaderFromFile (GL_FRAGMENT_SHADER, currFolder + "../shaders/ball.frag");
    program.Link ();

    geometry.reset (new GLngin::Sphere (position, 0.5f));
    geometry->Init ();
    ((GLngin::ParamSurface*)geometry.get ())->Create (32, 32);
}


void Ball::DrawImpl (const GLngin::Camera* const camera) const
{
    GLngin::Math::Mat4 MVP =    GLngin::Math::Mat4::Scale (scale) *
                                GLngin::Math::Mat4::Rotate (rotAngle, rotAxis) *
                                GLngin::Math::Mat4::Translate (position) *
                                camera->View () * camera->Proj ();

    program.Use ();
    program.SetUniformMat4 ("MVP", MVP);
    geometry->Draw ();
    program.UnUse ();
}
