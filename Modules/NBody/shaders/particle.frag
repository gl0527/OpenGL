#version 430

in vec2 fVelocity;

out vec4 outColor;

void main()
{
    outColor = vec4((fVelocity + 1.0) * 0.5, 0.5, 1.0);
}
