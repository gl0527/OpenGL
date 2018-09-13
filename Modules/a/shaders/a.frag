#version 330
precision highp float;

in vec3 color;				// variable input: interpolated color of vertex shader
out vec4 fragmentColor;		// output that goes to the raster memory as told by glBindFragDataLocation

void main() {
        fragmentColor = vec4(color, 1); // extend RGB to RGBA
}
