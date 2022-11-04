#include "Entity.h"

#include <glm/gtc/matrix_transform.hpp>

const glm::mat4& Entity::getModelMatrix() const
{
	return m_modelMatrix;
}

void Entity::computeModelMatrix()
{
	m_modelMatrix = glm::translate(glm::mat4(1.0), m_position);
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	m_modelMatrix = glm::scale(m_modelMatrix, m_scaleFactor);
}
