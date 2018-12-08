#version 330

in vec2 fTexCoord;
out vec4 outColor;

uniform sampler2D tex;


void drawBlacknWhite ()
{
    vec3 px = texture2D (tex, fTexCoord).xyz;
    outColor = dot (px, px) < 0.5 ? vec4 (0.0, 0.0, 0.0, 1.0) : vec4 (1.0, 1.0, 1.0, 1.0);
}


void averaging ()
{
    vec2 texSize = textureSize (tex, 0);
    float dx = 1.0 / texSize.x;
    float dy = 1.0 / texSize.y;

    mat3 prewittX = mat3 (1.0, 0.0, -1.0, 1.0, 0.0, -1.0, 1.0, 0.0, -1.0);
    mat3 prewittY = mat3 (1.0, 1.0, 1.0, 0.0, 0.0, 0.0, -1.0, -1.0, -1.0);

    vec4 sum;

    for(float y = fTexCoord.y - dy; y <= fTexCoord.y + dy; y=y+dy) {
        for(float x = fTexCoord.x - dx; x <= fTexCoord.x + dx; x=x+dx) {
            int iy = int((y-(fTexCoord.y - dy)) / dy);
            int ix = int((x-(fTexCoord.x - dx)) / dx);

            sum = sum + prewittX[iy][ix] * texture2D(tex, vec2(x,y));
        }
    }
    sum /= 9.0;
    outColor = sum;
}


void edgeGrad ()
{
    vec2 texSize = textureSize(tex, 0);
    float dx = 1.0 / texSize.x;
    float dy = 1.0 / texSize.y;

    vec4 leftNeighbor   = texture2D(tex, vec2(fTexCoord.x - dx, fTexCoord.y));
    vec4 rightNeighbor  = texture2D(tex, vec2(fTexCoord.x + dx, fTexCoord.y));
    vec4 topNeighbor    = texture2D(tex, vec2(fTexCoord.x, fTexCoord.y + dy));
    vec4 bottomNeighbor = texture2D(tex, vec2(fTexCoord.x, fTexCoord.y - dy));

    vec4 deltaX = (rightNeighbor - leftNeighbor);
    vec4 deltaY = (topNeighbor - bottomNeighbor);

    outColor = dot (deltaY, deltaY) > 0.01 ? vec4(1.0, 1.0, 1.0, 1.0) : vec4(0.0, 0.0, 0.0, 1.0);
}


void main()
{
    drawBlacknWhite ();
}
