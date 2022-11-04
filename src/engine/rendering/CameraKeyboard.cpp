#include "CameraKeyboard.h"

#include "../core/input/InputManager.h"
#include "../core/Time.h"

CameraKeyboard::CameraKeyboard(glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, glm::vec2 extent, ProjectionType projection = ProjectionType::PERSPECTIVE)
	: Camera(position, up, lookAt, extent, projection)
{
}

void CameraKeyboard::update()
{	
	auto pos = getPosition();
	auto dt = static_cast<float>(Time::deltaTime);

	if (InputManager::isPressed(GLFW_KEY_W))
		pos += m_cameraSpeed * m_front * dt;
	if (InputManager::isPressed(GLFW_KEY_S))
		pos -= m_cameraSpeed * m_front * dt;
	if (InputManager::isPressed(GLFW_KEY_A))
		pos -= glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f))) * m_cameraSpeed * dt;
	if (InputManager::isPressed(GLFW_KEY_D))
		pos += glm::normalize(glm::cross(m_front, glm::vec3(0.0f, 1.0f, 0.0f))) * m_cameraSpeed * dt;
	if (InputManager::isPressed(GLFW_KEY_Q))
		pos += m_cameraSpeed * m_up * dt;
	if (InputManager::isPressed(GLFW_KEY_R))
		pos -= m_cameraSpeed * m_up * dt;
	
	if (InputManager::isPressed(GLFW_KEY_I))
		m_pitch += m_acc;
	if (InputManager::isPressed(GLFW_KEY_J))
		m_yaw -= m_acc;
	if (InputManager::isPressed(GLFW_KEY_L))
		m_yaw += m_acc;
	if (InputManager::isPressed(GLFW_KEY_K))
		m_pitch -= m_acc;
	
	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);

	setPosition(pos);
	computeViewMatrix();
}
