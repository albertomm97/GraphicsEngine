#version 430
layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 modelViewMatrix;

void main()
{
	gl_Position = modelViewMatrix * vec4( VertexPosition, 1.0 );
	TexCoord = aTexCoord;
}