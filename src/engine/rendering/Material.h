#pragma once

#include "../core/common/Types.h"

#include "RenderProgram.h"
#include "Texture.h"

#include <vector>
#include <string>
#include <memory>

class Material
{
public:
	virtual ~Material() = default;
	virtual void addShaders(const std::vector<std::string>& shadersPath) = 0;
	virtual void prepare() = 0;

	inline void setRenderProgram(std::shared_ptr<RenderProgram> renderProgram) { m_renderProgram = renderProgram; }
	inline std::shared_ptr<RenderProgram> getRenderProgram() const { return m_renderProgram; }
	inline u32 getProgramHandle() { return m_renderProgram->getHandle(); }

	inline void setTexture(std::shared_ptr<Texture> texture) { m_texture = texture; }
	inline std::shared_ptr<Texture> getTexture() const { return m_texture; }
	inline u32 getTextureHandle() { return m_texture->getHandle(); }

	inline void setColor(glm::vec4 color) { m_color = color; }
	inline const glm::vec4& getColor() const { return m_color; }

	inline void setShininess(i32 shininess) { m_shininess = shininess; }
	inline i32 getShininess() const { return m_shininess; }

private:
	std::shared_ptr<RenderProgram> m_renderProgram;
	std::shared_ptr<Texture> m_texture;
	glm::vec4 m_color;
	i32 m_shininess;
};