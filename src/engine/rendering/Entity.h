#pragma once

#include "../core/common/Types.h"

#include <vector>
#include <glm/glm.hpp>

class Entity
{
public:
	/*Entity(glm::vec3 position)
		: m_position{ position } {}

	Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
		: m_position{ position }, m_rotation{ rotation }, m_scaleFactor{ scale } {}*/

	Entity() = default;
	virtual ~Entity() = default;

	inline glm::vec3 getPosition() const { return m_position; };
	inline glm::vec3 getRotation() const { return m_rotation; };
	inline glm::vec3 getScaleFactor() const { return m_scaleFactor; };

	void setPosition(glm::vec3 position) { m_position = position; }
	void setRotation(glm::vec3 rotation) { m_rotation = rotation; }
	void setScaleFactor(glm::vec3 scaleFactor) { m_scaleFactor = scaleFactor; }

	const glm::mat4& getModelMatrix() const;
	void computeModelMatrix();

	virtual void update() = 0;

protected:
	u32 m_id;
	glm::vec3 m_position{};
	glm::vec3 m_rotation{};
	glm::vec3 m_scaleFactor{};
	glm::mat4 m_modelMatrix{};
};

