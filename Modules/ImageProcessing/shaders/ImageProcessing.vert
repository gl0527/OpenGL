#version 330

in vec4 vData;
out vec2 fTexCoord;

void main(void) {
   gl_Position = vec4(vData.xy, 0.0, 1.0);
   fTexCoord = vData.zw;
}
