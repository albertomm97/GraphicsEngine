#pragma once

#include "../core/common/Types.h"

#include <memory>
#include <vector>
#include <string>

class Render;
class Material;
class Texture;

class FactoryEngine
{
public:
	explicit FactoryEngine() = default;
	std::unique_ptr<Render> getNewRenderer(RendererType desiredRenderer);

	std::shared_ptr<Material> getNewMaterial(std::vector<std::string>& shadersPath);
	std::shared_ptr<Material> getNewRawMaterial();

	std::shared_ptr<Texture> getNewTexture(const std::string& texturePath);

	inline RendererType selectedGraphicsBackend() { return m_rendererType; }

private:
	RendererType m_rendererType;
};

