#version 430

in vec2 fVelocity;

out vec4 outColor;

void main()
{
    outColor = vec4 ((fVelocity + vec2 (1.0, 1.0)) * 0.5, 0.7, 1.0);
}
