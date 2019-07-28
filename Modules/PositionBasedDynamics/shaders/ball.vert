#version 430

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vNorm;
layout(location = 2) in vec2 vUV;

uniform mat4 MVP;

out vec3 fNorm;
out vec2 fUV;

void main()
{
    gl_Position = vec4 (vPos, 1.0) * MVP;
    fNorm = vNorm;
    fUV = vUV;
}
