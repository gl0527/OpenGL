#version 330
layout (location = 0) in vec3 vCoords;

out vec3 tCoords;
uniform mat4 viewProj;

void main()
{
    tCoords = vCoords;
    gl_Position = viewProj * vec4 (vCoords, 1.0);
}
