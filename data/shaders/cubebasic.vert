#version 430
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec4 VertexColor;

out vec4 Color;

uniform mat4 modelViewMatrix;

void main()
{
	Color = VertexColor;
	gl_Position = modelViewMatrix * vec4( VertexPosition, 1.0 );
}