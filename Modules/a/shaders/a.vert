#version 330
precision highp float;

uniform mat4 MVP;			// Model-View-Projection matrix in row-major format

layout(location = 0) in vec2 vertexPosition;	// Attrib Array 0
layout(location = 1) in vec3 vertexColor;	    // Attrib Array 1
out vec3 color;									// output attribute

void main() {
	color = vertexColor;														// copy color from input to output
	gl_Position = vec4(vertexPosition.x, vertexPosition.y, 0, 1) * MVP; 		// transform to clipping space
}
