#pragma once

#include "../Texture.h"

#include <map>

class GLTexture : public Texture
{
public:
	GLTexture() = default;
	~GLTexture() override = default;

	void loadTexture(const std::string& path) override;
	u32 getHandle() override;
	glm::ivec2 getSize() override;
	void bind() override;

private:
	u32 m_handle{};
	i32 m_width{};
	i32 m_height{};
};

