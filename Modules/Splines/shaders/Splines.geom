#version 330
#extension GL_EXT_gpu_shader4: enable
#extension GL_EXT_geometry_shader4: enable

layout (lines_adjacency) in;
layout (line_strip, max_vertices=200) out;

in vec2 gData[];
out vec4 gColor;


void EmitCurve (inout mat4 mat)
{
    for (float t = 0.0; t <= 1.0; t += 0.02) {
        vec4 p0 = vec4 (t*t*t, t*t, t, 1.0) * mat;
        gl_Position = vec4 (p0.x * gData[0] + p0.y * gData[1] + p0.z * gData[2] + p0.w * gData[3], 0.0, 1.0);
        EmitVertex ();
    }
    EndPrimitive ();
}


void main ()
{
    // Emit Bezier curve
    gColor = vec4 (1.0, 1.0, 0.0, 1.0);
    mat4 bezierMat = mat4 (-1.0, 3.0, -3.0, 1.0,
                            3.0, -6.0, 3.0, 0.0,
                           -3.0, 3.0, 0.0, 0.0,
                            1.0, 0.0, 0.0, 0.0);
    EmitCurve (bezierMat);

    // Emit control polygon
    gColor = vec4 (0.0, 1.0, 1.0, 1.0);
    for (int i = 0; i < gl_VerticesIn; ++i) {
        gl_Position = vec4 (gData[i], 0.0, 1.0);
        EmitVertex ();
    }
    EndPrimitive ();
}
