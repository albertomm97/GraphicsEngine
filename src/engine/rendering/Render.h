#pragma once

#include "../core/common/Types.h"

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <iostream>

class Object;

struct PerFrameCameraData
{
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::vec3 cameraPosition;
	f32 padding;
};

struct CameraUniformBuffer
{
	CameraUniformBuffer() = default;
	CameraUniformBuffer(u32 handle, const PerFrameCameraData* data)
		: bufferHandle{ handle }, cameraData{ data }
	{}
	
	u32 bufferHandle;
	const PerFrameCameraData* cameraData;
};

struct PerframePhongLightData
{

	PerframePhongLightData(glm::vec3 position, glm::vec4 color, glm::vec3 ambient, f32 ambStrengh, f32 specStrengh)
		: color{ color },
		position{ position },
		ambient{ ambient },
		ambientStrengh{ ambStrengh },
		specularStrengh{ specStrengh },
		enabled{ true }
	{}

	PerframePhongLightData(glm::vec3 position, glm::vec4 color, glm::vec3 ambient, f32 ambStrengh, f32 specStrengh, f32 constAttenuation, f32 linAttenuation, f32 quadAttenuation, glm::vec3 direction, i32 type)
		: color{ color },
		position{ position },
		ambient{ ambient },
		ambientStrengh{ ambStrengh },
		specularStrengh{ specStrengh },
		type{ type },
		enabled{ true },
		kAttenuation{ constAttenuation },
		lAttenuation{ linAttenuation },
		qAttenuation{ quadAttenuation },
		direction{ direction }
	{}

	glm::vec4 color;
	glm::vec3 position;
	f32 padding1;
	glm::vec3 ambient;
	f32 ambientStrengh;
	f32 specularStrengh;
	//glm::vec3 padding2;

	i32 type;
	i32 enabled;
	f32 kAttenuation;
	f32 lAttenuation;
	f32 qAttenuation;
	glm::vec2 padding2;
	
	glm::vec3 direction;
	f32 padding3;
};

struct PhongLightUniformBuffer
{
	PhongLightUniformBuffer() = default;
	PhongLightUniformBuffer(u32 handle, const PerframePhongLightData* data, u32 count)
		: bufferHandle{ handle }, lightData{ data }, lightCount{ count }
	{}

	u32 bufferHandle;
	const PerframePhongLightData* lightData;
	u32 lightCount;
};

struct MaterialData
{
	glm::vec4 color;
	i32 shininess;
};

class Render
{
public:
	virtual ~Render() = default;

	virtual void init() = 0;
	virtual void setupObject(Object* object) = 0;
	virtual void removeObject(Object* object) = 0;
	virtual void draw() = 0;
	virtual void setCameraUniformBuffer(std::string name, PerFrameCameraData* data) = 0;
	virtual void setPhongLightUniformBuffer(std::string name, const std::vector<PerframePhongLightData>& data) = 0;
};

