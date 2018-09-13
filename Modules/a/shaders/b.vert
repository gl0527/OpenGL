#version 330
precision highp float;

uniform mat4 rayDirMatrix;

layout(location = 0) in vec3 vertexPosition;
layout(location = 2) in vec2 vertexTexCoord;
out vec3 rayDir;
out vec2 tex;

void main(void) {
	rayDir = (vec4(vertexPosition, 1.0) * rayDirMatrix).xyz;
	tex = vertexTexCoord;
	gl_Position = vec4(vertexPosition, 1.0);
}
