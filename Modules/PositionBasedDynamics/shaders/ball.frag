#version 430

in vec3 fNorm;
in vec2 fUV;

out vec4 outColor;


void main()
{
    outColor = vec4 (normalize (fNorm), 1.0);
}
