#version 330

in vec2 fTexCoord;
out vec4 outColor;

uniform sampler2D tex;
uniform vec2 step;

int isAlive(float x, float y)
{
    return int(texture2D(tex, fTexCoord + vec2(x, y) * step).r);
}

void main()
{
    int aliveNeighbors =    isAlive(-1.0, -1.0) +
                            isAlive( 0.0, -1.0) +
                            isAlive( 1.0, -1.0) +
                            isAlive(-1.0,  0.0) +
                            isAlive( 1.0,  0.0) +
                            isAlive(-1.0,  1.0) +
                            isAlive( 0.0,  1.0) +
                            isAlive( 1.0,  1.0);

    if (aliveNeighbors == 3) {
        outColor = vec4(1.0, 1.0, 1.0, 1.0);
    } else if (aliveNeighbors == 2) {
        float current = float(isAlive(0.0, 0.0));
        outColor = vec4(current, current, current, 1.0);
    } else {
        outColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
