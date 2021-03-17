#version 330

in vec3 vPosition;
in vec2 vTexCoord;

out vec2 fTexCoord;

void main(void) {
   gl_Position = vec4(vPosition, 1.0);
   fTexCoord = vTexCoord;
}
