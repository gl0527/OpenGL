#version 430

layout(location = 0) in vec4 vParticleData;

out vec2 fVelocity;

void main()
{
    gl_Position = vec4 (vParticleData.xy, 0.0, 1.0);
    fVelocity = vParticleData.zw;
}
