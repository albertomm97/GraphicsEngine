#version 430

const int MAX_LIGHTS = 8;

const int DIRECTIONAL_LIGHT = 0;
const int POINT_LIGHT = 1;

const int TRUE = 1;
const int FALSE = 0;

// Position and ambient are vec4 because of padding (ambient has its strengh in fourth component)
struct LightData {
	vec4 color;
	vec4 position;
	vec4 ambient;
	float specularStrengh;
	int type;
	int enabled;

	float kAttenuation;
	float lAttenuation;
	float qAttenuation;

	vec4 direction;
};

layout (std140, binding = 1) uniform Light {	
	LightData lights[MAX_LIGHTS];
};

struct Material
{
	vec4 color;
	int shininess;
};

vec3 calculateAmbientLight(vec3 ambient, vec4 color, float strengh) {
	return ambient * color.xyz * strengh;
}

vec3 calculateDiffuseLight(vec3 lightPosition, vec3 fragPosition, vec3 normal, vec4 color) {
	vec3 n = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPosition);
	float diffuse = max(dot(n, lightDir), 0.0);
	return diffuse * color.xyz;
}

vec3 calculateSpecularLight(vec3 lightPosition, vec3 cameraPosition, vec3 fragPosition, vec3 normal, vec4 color, float strengh, int shininess) {
	vec3 n = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPosition);
	vec3 viewDir = normalize(cameraPosition - fragPosition);
	vec3 reflectDir = reflect(-lightDir, n);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular = strengh * spec * color.xyz;  
	return specular;
}

//uniform sampler2D ourTexture;

uniform Material mat;

in vec3 FragPos;
in vec3 Normal;
in vec3 CameraPosition;
//in vec2 TexCoord;

out vec4 FragColor;

void main() 
{
	vec3 lightResult = vec3(0.0, 0.0, 0.0);
	vec3 norm = normalize(Normal);

	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		if (lights[i].enabled == FALSE)
			continue;

		if (lights[i].type == POINT_LIGHT)
		{
			vec4 color = lights[i].color;
			vec3 pos = lights[i].position.xyz;
			float specStrengh = lights[i].specularStrengh;

			vec3 diffuse = calculateDiffuseLight(pos, FragPos, Normal, color);
			vec3 specular = calculateSpecularLight(pos, CameraPosition, FragPos, Normal, color, specStrengh, mat.shininess);

			float distance = length(pos - FragPos);
			float attenuation = 1.0 / (lights[i].kAttenuation + lights[i].lAttenuation * distance + lights[i].qAttenuation * (distance * distance));    

			diffuse *= attenuation;
			specular *= attenuation;

			lightResult += vec3(diffuse + specular);
		}

		if (lights[i].type == DIRECTIONAL_LIGHT)
		{
			vec3 lightDir = normalize(-lights[i].direction.xyz);
			float diff = max(dot(norm, lightDir), 0.0);
			vec3 diffuse = diff * lights[i].color.rgb; 

			vec3 viewDir = normalize(CameraPosition - FragPos);
			vec3 reflectDir = reflect(-lightDir, norm);  
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), mat.shininess);
			vec3 specular = lights[i].specularStrengh * spec * lights[i].color.rgb;  

			lightResult += diffuse + specular;
		} 
	}

	vec3 ambient = calculateAmbientLight(lights[0].ambient.xyz, lights[0].color, lights[0].ambient.w);

	FragColor = vec4(ambient + lightResult, 1.0) * mat.color;
}