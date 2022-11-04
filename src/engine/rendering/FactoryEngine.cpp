#include "FactoryEngine.h"
#include "GL1Render/GL1Render.h"
#include "GL4Render/GLRender.h"
#include "GL4Render/GLMaterial.h"
#include "GL4Render/GLTexture.h"

std::unique_ptr<Render> FactoryEngine::getNewRenderer(RendererType desiredRenderer)
{
    m_rendererType = desiredRenderer;
    if (m_rendererType == RendererType::GL1Render)
    {
        auto renderer = std::make_unique<GL1Render>();
        renderer->init();
        return renderer;
    }

    if (m_rendererType == RendererType::GL4Render)
    {
        auto renderer = std::make_unique<GLRender>();
        return renderer;
    }
       
    return nullptr;
}

std::shared_ptr<Material> FactoryEngine::getNewMaterial(std::vector<std::string>& shadersPath)
{
    if (m_rendererType == RendererType::GL4Render)
    {
        auto material = std::make_shared<GLMaterial>();
        material->addShaders(shadersPath);
        return material;
    }
}

std::shared_ptr<Material> FactoryEngine::getNewRawMaterial()
{
	if (m_rendererType == RendererType::GL4Render)
	{
		auto material = std::make_shared<GLMaterial>();
		return material;
	}
}

std::shared_ptr<Texture> FactoryEngine::getNewTexture(const std::string& texturePath)
{
    if (m_rendererType == RendererType::GL4Render)
    {
        auto texture = std::make_shared<GLTexture>();
        texture->loadTexture(texturePath);
        return texture;
    }
}
