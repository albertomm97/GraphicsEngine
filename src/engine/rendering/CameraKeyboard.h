#pragma once
#include "Camera.h"

class CameraKeyboard : public Camera
{
public:
	explicit CameraKeyboard(glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, glm::vec2 extent, ProjectionType projection);
	~CameraKeyboard() override = default;
	void update() override;
private:
	f32 m_yaw{ -90.0f }, m_pitch{ 0.0f }, m_acc{ 1.5f };
	f32 m_cameraSpeed{ 2.0f };
};

