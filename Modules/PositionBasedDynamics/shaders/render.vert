#version 430

layout(location = 0) in vec4 vPosition;

uniform mat4 MVP;

void main()
{
    gl_Position = vPosition * MVP;
}
