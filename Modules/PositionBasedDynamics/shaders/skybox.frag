#version 330

in vec3 tCoords;
uniform samplerCube cubeMap;
out vec4 fragColor;

void main ()
{
    fragColor = texture (cubeMap, normalize (tCoords));
}
