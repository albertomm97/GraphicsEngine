#pragma once

#include "../Render.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GL1Render : public Render
{
public:
	explicit GL1Render();
	~GL1Render() override;
	void init() override;
	void setupObject(Object* object) override;
	void removeObject(Object* object) override;
	void draw() override;
	void setCameraUniformBuffer(std::string name, PerFrameCameraData* data) override;
	void setPhongLightUniformBuffer(std::string name, const std::vector<PerframePhongLightData>& data) override;

private:
	std::vector<Object*> m_objects;
};

