#version 430

layout(location = 0) in vec4 vPosition;

uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * vPosition;
}
