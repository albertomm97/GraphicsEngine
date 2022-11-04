#pragma once

#include "../core/common/Types.h"

#include <glm/glm.hpp>

#include <string>

class Texture
{
public:
	virtual ~Texture() = default;
	virtual void loadTexture(const std::string& path) = 0;
	virtual u32 getHandle() = 0;
	virtual glm::ivec2 getSize() = 0;
	virtual void bind() = 0;
};