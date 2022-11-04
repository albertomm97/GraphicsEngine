#include "OrbitalLight.h"

#include "../core/Time.h"
#include <glm/gtx/string_cast.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

OrbitalLight::OrbitalLight(const glm::vec3& attach, glm::vec3 position, glm::vec4 color, glm::vec3 ambient, f32 ambientStrengh, f32 specularStrengh, f32 kAttenuation, f32 lAttenuation, f32 qAttenuation)
	: m_attachPosition{ attach }
{
	setLightType(LightType::POINT);
	setPosition(position);
	setColor(color);
	setAmbient(ambient);
	setAmbientStrengh(ambientStrengh);
	setSpecularStrengh(specularStrengh);
	setConstAttenuation(kAttenuation);
	setLinearAttenuation(lAttenuation);
	setQuadraticAttenuation(qAttenuation);
	enableLight(true);
}

void OrbitalLight::update()
{
	auto transform = glm::translate(glm::mat4(1), -m_attachPosition);
	transform = glm::rotate(transform, static_cast<f32>(m_rotSpeed * Time::deltaTime), m_rotationAxis);
	transform = glm::translate(transform, m_attachPosition);

	glm::vec4 pos(m_position.x, m_position.y, m_position.z, 0.0f);
	setPosition(glm::vec3(transform*pos));
}

const glm::vec3& OrbitalLight::getAttachPosition() const
{
	return m_attachPosition;
}

void OrbitalLight::setRotationSpeed(f32 speed)
{
	m_rotSpeed = speed;
}

f32 OrbitalLight::getRotationSpeed() const
{
	return m_rotSpeed;
}

void OrbitalLight::setRotationAxis(glm::vec3 axis)
{
	m_rotationAxis = axis;
}

glm::vec3 OrbitalLight::getRotationAxis() const
{
	return m_rotationAxis;
}

