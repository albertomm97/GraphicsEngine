#pragma once
#include "Camera.h"
class CameraFly : public Camera
{
public:
	explicit CameraFly(glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, glm::vec2 windowExtent, ProjectionType projection);
	~CameraFly() override = default;
	
	void update() override;

private:
	f32 m_yaw{ -90.0f }, m_pitch{ 0.0f }, m_lastX{ 0.0f }, m_lastY{ 0.0f };
	f32 m_cameraSpeed{ 0.9f };
	f32 m_sensitivity{ 0.25f };
	glm::vec2 m_windowExtent;
};

