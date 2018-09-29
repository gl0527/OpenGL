#version 330

in vec2 fTexCoord;
out vec4 outColor;


vec2 sqr(vec2 v)
{
    return vec2 (v.x * v.x - v.y * v.y, 2.0 * v.x * v.y);
}


void drawJulia(vec2 z, vec2 c)
{
    int iter = 0;
    const int MaxIter = 1000;
    while(iter < MaxIter && length(z) * length(z) < 4.0) {
        z = sqr(z) + c;
        iter++;
    }
    outColor = iter < MaxIter*0.5 ? vec4(float(iter) / MaxIter) : vec4(fTexCoord, 0.0, 1.0);
}


void drawMandelbrot(vec2 c)
{
    vec2 z = c;
    int iter = 0;
    const int MaxIter = 1000;
    while(iter < MaxIter && length(z) * length(z) < 4.0) {
        z = sqr(z) + c;
        iter++;
    }
    outColor = iter < MaxIter*0.5 ? vec4(float(iter) / MaxIter) : vec4(fTexCoord, 0.0, 1.0);
}


void main()
{
    vec2 z = vec2 (4.0 * (fTexCoord.x - 0.5), 4.0 * (fTexCoord.y - 0.5));
    vec2 c = vec2 (-0.7269, 0.1889);

    drawJulia (z, c);
    //drawMandelbrot (z);
}
