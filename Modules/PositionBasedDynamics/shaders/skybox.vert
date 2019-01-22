#version 330
layout (location = 0) in vec3 vCoords;

out vec3 tCoords;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    tCoords = vCoords;
    gl_Position = proj * view * vec4 (vCoords, 1.0);
}
