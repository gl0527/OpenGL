#version 330

in vec2 fTexCoord;
out vec4 outColor;

uniform sampler2D tex;

void main()
{
    outColor = texture2D(tex, fTexCoord);
}
