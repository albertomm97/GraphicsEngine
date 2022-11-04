#pragma once

#include "Entity.h"

#include <glm/glm.hpp>

enum class ProjectionType
{
	PERSPECTIVE = 0,
	ORTHOGONAL
};

enum class CameraType
{
	KEYBOARD = 0,
	FPS,
	FLY
};

class Camera : public Entity
{
public:
	explicit Camera(glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, glm::vec2 extent, ProjectionType projection);
	virtual ~Camera() = default;
	glm::mat4 getProjection() const;
	glm::mat4 getView() const;
	void computeViewMatrix();
	void computeProjectionMatrix(ProjectionType type);

	const glm::vec3& getFrontPosition() const;

	virtual void update() = 0;

protected:
	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::vec3 m_up;
	glm::vec3 m_lookAt;
	glm::vec3 m_front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec2 m_extent;
	ProjectionType m_projectionType;
};

