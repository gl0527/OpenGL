#version 330

in vec4 vPosition;
in vec2 vTexCoord;

out vec2 fTexCoord;

void main(void) {
   gl_Position = vPosition;
   fTexCoord = vTexCoord;
}
