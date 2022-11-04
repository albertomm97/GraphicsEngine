#version 430
layout (location = 0) in vec3 VertexPosition;
//layout (location = 1) in vec2 aTexCoord;
layout (location = 1) in vec3 aNormal;


layout(std140, binding = 0) uniform Camera {	
	mat4 projection;
	mat4 view;
	vec3 position;
} camera;

uniform mat4 model;

out vec3 FragPos;
out vec3 Normal;
out vec3 CameraPosition;
//out vec2 TexCoord;

void main()
{
	FragPos = vec3(model * vec4(VertexPosition, 1.0));
	Normal = mat3(transpose(inverse(model))) * aNormal;
	CameraPosition = camera.position;
	//TexCoord = aTexCoord;

	gl_Position = camera.projection * camera.view * model * vec4( VertexPosition, 1.0 );
}