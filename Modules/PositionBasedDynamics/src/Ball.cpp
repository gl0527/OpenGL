#include "Ball.hpp"

#include "Debug.hpp"
#include "Mat4.hpp"
#include "Camera.hpp"
#include "Sphere.hpp"
#include "RenderState.hpp"
#include <GL/glew.h>
#include <cstdio>
#include <cstring>


void Ball::InitImpl ()
{
    std::string currFolder (FOLDER);

    program.Init (currFolder + "../shaders/ball.vert", std::nullopt, std::nullopt, std::nullopt, currFolder + "../shaders/ball.frag", std::nullopt);

    geometry.reset (new GLngin::Sphere (position, 0.5f));
    geometry->Init ();
    ((GLngin::ParamSurface*)geometry.get ())->Create (32, 32);
}


void Ball::DrawImpl (const GLngin::RenderState& renderState)
{
    GLngin::Math::Mat4 MVP =    GLngin::Math::Mat4::Scale (scale) *
                                GLngin::Math::Mat4::Rotate (rotAngle, rotAxis) *
                                GLngin::Math::Mat4::Translate (position) *
                                renderState.viewProj.value ();

    program.Bind ();
    program.SetUniformMat4 ("MVP", MVP);
    geometry->Draw ();
    program.UnBind ();
}
