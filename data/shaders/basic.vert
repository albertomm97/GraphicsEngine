#version 430
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec4 VertexColor;

out vec4 Color;

layout(std140, binding = 0) uniform Camera {	
	mat4 projection;
	mat4 view;
	vec3 position;
} camera;

uniform mat4 model;

void main()
{
	Color = VertexColor;
	gl_Position = camera.projection * camera.view * model * vec4( VertexPosition, 1.0 );
}