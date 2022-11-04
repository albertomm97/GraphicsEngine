#version 430
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec4 VertexColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 Color;
out vec2 TexCoord;

uniform mat4 modelViewMatrix;

void main()
{
	Color = VertexColor;
	gl_Position = modelViewMatrix * vec4( VertexPosition, 1.0 );
	TexCoord = aTexCoord;
}