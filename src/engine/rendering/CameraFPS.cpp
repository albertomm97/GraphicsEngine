#include "CameraFPS.h"

#include "../core/input/InputManager.h"
#include "../core/Time.h"

#include <iostream>

CameraFPS::CameraFPS(glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, glm::vec2 windowExtent, ProjectionType projection)
	: Camera(position, up, lookAt, windowExtent, projection)
{
	m_windowExtent = windowExtent;
	m_lastX = m_windowExtent.x / 2;
	m_lastY = m_windowExtent.y / 2;
}

void CameraFPS::update()
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

	pos.y = 0.015f;
	setPosition(pos);

	f32 x = InputManager::getMouseX();
	f32 y = InputManager::getMouseY();

	f32 xoffset = x - m_lastX;
	f32 yoffset = m_lastY - y;

	m_lastX = x;
	m_lastY = y;

	m_yaw += xoffset * m_sensitivity;
	m_pitch += yoffset * m_sensitivity;

	if (m_pitch > 60.0f)
		m_pitch = 60.0f;
	if (m_pitch < -60.0f)
		m_pitch = -60.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = glm::normalize(front);

	computeViewMatrix();
}
