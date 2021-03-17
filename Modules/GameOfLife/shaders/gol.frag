#version 330

in vec2 fTexCoord;
out vec4 outColor;

uniform sampler2D tex;

int isAlive(vec2 uv)
{
    return texture2D(tex, uv).r > 0.5 ? 1 : 0;
}

void main()
{
    vec2 px = 1.0 / textureSize(tex, 0);

    int aliveNeighbors = 0;
    for (int y = -1; y <= 1; ++y) {
        for (int x = -1; x <= 1; ++x) {
            aliveNeighbors += isAlive(fTexCoord + vec2(float(x), float(y)) * px);
        }
    }
    int isCurrentAlive = isAlive(fTexCoord);
    aliveNeighbors -= isCurrentAlive;

    if (aliveNeighbors == 3) {
        outColor = vec4(1, 1, 1, 1);
    } else if (aliveNeighbors == 2) {
        outColor = vec4(isCurrentAlive, isCurrentAlive, isCurrentAlive, 1);
    } else {
        outColor = vec4(0, 0, 0, 1);
    }
}
