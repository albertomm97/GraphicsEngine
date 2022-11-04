#pragma once
#include "Camera.h"

class CameraFPS : public Camera
{
public:
	explicit CameraFPS(glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, glm::vec2 windowExtent, ProjectionType projection);
	~CameraFPS() override = default;

	void update() override;

private:
	f32 m_yaw{ -90.0f }, m_pitch{ 0.0f }, m_lastX{ 0.0f }, m_lastY{ 0.0f };
	f32 m_cameraSpeed{ 0.1f };
	f32 m_sensitivity{ 0.15f };
	glm::vec2 m_windowExtent;
};

