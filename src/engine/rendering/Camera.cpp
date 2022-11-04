#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, glm::vec2 extent, ProjectionType projection = ProjectionType::PERSPECTIVE)
	: m_up{ up }, m_lookAt{ lookAt }, m_extent{ extent }, m_projectionType{ projection }
{
	setPosition(position);
	computeViewMatrix();
	if (m_projectionType == ProjectionType::PERSPECTIVE)
	{
		m_projection = glm::perspective(45.0f, static_cast<float>(m_extent.x / m_extent.y), 0.01f, 1000.0f);
	}
	else
	{
		m_projection = glm::ortho(0.0f, m_extent.x, m_extent.y, 600.0f, 0.1f, 100.0f);
	}
}

glm::mat4 Camera::getProjection() const
{
	return m_projection;
}

glm::mat4 Camera::getView() const
{
	return m_view;
}

void Camera::computeViewMatrix()
{
	m_view = glm::lookAt(getPosition(), getPosition() + m_front, m_up);
}

void Camera::computeProjectionMatrix(ProjectionType type = ProjectionType::PERSPECTIVE)
{
	if (m_projectionType == ProjectionType::PERSPECTIVE)
	{
		m_projection = glm::perspective(45.0f, static_cast<float>(m_extent.x / m_extent.y), 0.01f, 1000.0f);
	}
	else
	{
		m_projection = glm::ortho(0.0f, m_extent.x, m_extent.y, 600.0f, 0.1f, 100.0f);
	}
}

const glm::vec3& Camera::getFrontPosition() const
{
	return m_front;
}
