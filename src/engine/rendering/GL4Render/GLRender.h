#pragma once

#include "../Render.h"
#include "RenderInfo.h"

#include <glm/glm.hpp>

#include <unordered_map>
#include <map>
#include <functional>
#include <variant>
#include <any>

class GLRender : public Render
{
public:
	explicit GLRender();
	~GLRender() override;
	
	void init() override;
	void setupObject(Object* object) override;
	void removeObject(Object* object) override;
	void draw() override;
	void setCameraUniformBuffer(std::string name, PerFrameCameraData* data) override;
	void setPhongLightUniformBuffer(std::string name, const std::vector<PerframePhongLightData>& data) override;

private:
	void drawDefault(RenderInfo& renderInfo);
	void drawIndices(RenderInfo& renderInfo);
	void drawInstanced(RenderInfo& renderInfo);

	void updateUniformBuffers() const;

private:
	using MeshID = u32;
	// std::map<std::string, UniformBufferData> m_uniformBuffers;
	std::unordered_map<MeshID, RenderInfo> m_renderObjects;
	std::unordered_map<DrawType, std::function<void(RenderInfo&)>> m_drawCommands;
	CameraUniformBuffer m_cameraUbo;
	PhongLightUniformBuffer m_lightUbo;
};

