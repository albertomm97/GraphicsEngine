#pragma once
#include "Light.h"

class OrbitalLight : public Light
{
public:
	OrbitalLight(const glm::vec3& attach, glm::vec3 position, glm::vec4 color, glm::vec3 ambient, f32 ambientStrengh, f32 specularStrengh, f32 kAttenuation, f32 lAttenuation, f32 qAttenuation);
	~OrbitalLight() override = default;

	const glm::vec3& getAttachPosition() const;

	void setRotationSpeed(f32 speed);
	f32 getRotationSpeed() const;

	void setRotationAxis(glm::vec3 axis);
	glm::vec3 getRotationAxis() const;

	void update() override;

private:
	const glm::vec3& m_attachPosition;
	glm::vec3 m_rotationAxis;
	f32 m_rotSpeed;
};

