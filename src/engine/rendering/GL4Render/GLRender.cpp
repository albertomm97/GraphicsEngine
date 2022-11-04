#include "GLRender.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "RenderInfo.h"
#include "GLProgram.h"

#include "../Object.h"
#include "../Mesh.h"
#include "../Material.h"


#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <map>
#include <tuple>


GLRender::GLRender()
{
	init();
}

GLRender::~GLRender()
{

}

void GLRender::init()
{
	glewExperimental = GL_TRUE;
	int glewState = glewInit();
	if (glewState != GLEW_OK)
		std::cout << "Error glew\n";

	glEnable(GL_DEPTH_TEST);

	m_drawCommands[DrawType::DEFAULT] = [this](RenderInfo& renderInfo) { drawDefault(renderInfo); };
	m_drawCommands[DrawType::INDICES] = [this](RenderInfo& renderInfo) { drawIndices(renderInfo); };
	m_drawCommands[DrawType::INSTANCED] = [this](RenderInfo& renderInfo) { drawInstanced(renderInfo); };
}

void GLRender::setupObject(Object* object)
{
	// Loop through and setup all meshes
	auto objectMeshes = object->getMesh();
	for (auto mesh : objectMeshes)
	{
		auto meshId = mesh->getId();
		auto material = mesh->getMaterial();
		auto programHandle = material->getProgramHandle();

		// TODO: Instanced rendering if we have more than one object with the same mesh
		if (m_renderObjects.count(meshId) == 1)
		{
			std::cout << "Object already in render objects\n";
			// Get Object info

			// Add object info to RenderInfo on the map so we can drawInstanced

			// Set drawtype to instanced
		}

		// Dentro de Mesh seguramente, no sabria donde ponerlo
		auto vao = std::make_unique<VertexArray>();
		vao->bind();

		auto& vertices = mesh->getVerticesList();
		auto vbo = std::make_unique<VertexBuffer>(vertices.data(), sizeof(vertices[0]) * vertices.size());
		vbo->bind();

		auto& indices = mesh->getIndicesList();
		std::unique_ptr<IndexBuffer>ib{};
		if (indices.size() > 0)
		{
			ib = std::make_unique<IndexBuffer>(indices.data(), sizeof(indices[0]) * indices.size());
			ib->bind();
		}

		material->prepare();

		if (indices.size() > 0)
		{
			m_renderObjects.emplace(std::pair<MeshID, RenderInfo>(
				meshId,
				RenderInfo(std::move(vao), std::move(vbo), std::move(ib), material, indices.size(), object)
			));
		}
		else
		{
			m_renderObjects.emplace(std::pair<MeshID, RenderInfo>(
				meshId,
				RenderInfo(std::move(vao), std::move(vbo), material, vertices.size(), object)
			));
		}
	}
}


void GLRender::removeObject(Object* object)
{
	
}

void GLRender::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	updateUniformBuffers();

	for (auto& renderElement : m_renderObjects) 
	{
		auto& renderInfo = renderElement.second;
		auto& drawCommand = m_drawCommands[renderInfo.drawType];
		drawCommand(renderInfo);
	}
}

void GLRender::setCameraUniformBuffer(std::string name, PerFrameCameraData* data)
{
	u32 uboHandle;
	glGenBuffers(1, &uboHandle);
	glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(PerFrameCameraData), data, GL_DYNAMIC_DRAW);
	
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, uboHandle);

	m_cameraUbo = CameraUniformBuffer(uboHandle, data);
}

void GLRender::setPhongLightUniformBuffer(std::string name, const std::vector<PerframePhongLightData>& data)
{
	u32 uboHandle;
	glGenBuffers(1, &uboHandle);
	glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
	glBufferData(GL_UNIFORM_BUFFER, data.size() * sizeof(PerframePhongLightData), data.data(), GL_DYNAMIC_DRAW);

	glBindBufferBase(GL_UNIFORM_BUFFER, 1, uboHandle);

	m_lightUbo = PhongLightUniformBuffer(uboHandle, data.data(), data.size());
}

void GLRender::drawDefault(RenderInfo& renderInfo)
{
	renderInfo.prepareForRender();
	auto material = renderInfo.material;
	auto renderProgram = material->getRenderProgram();

	renderProgram->setUniformMat4("model", renderInfo.object->getModelMatrix());

	renderProgram->setUniformVec4("mat.color", material->getColor());
	renderProgram->setUniformI("mat.shininess", material->getShininess());

	glDrawArrays(GL_TRIANGLES, 0, renderInfo.count);
}

void GLRender::drawIndices(RenderInfo& renderInfo)
{
	renderInfo.prepareForRender();

	auto material = renderInfo.material;
	auto renderProgram = material->getRenderProgram();
	
	renderProgram->setUniformMat4("model", renderInfo.object->getModelMatrix());
	
	renderProgram->setUniformVec4("mat.color", material->getColor());
	renderProgram->setUniformI("mat.shininess", material->getShininess());

	glDrawElements(GL_TRIANGLES, renderInfo.count, GL_UNSIGNED_INT, 0);
}

void GLRender::drawInstanced(RenderInfo& renderInfo)
{
	renderInfo.vao->bind();
	//glDrawArraysInstanced();
}

void GLRender::updateUniformBuffers() const
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_cameraUbo.bufferHandle);
	// get pointer
	void* ptr1 = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
	// now copy data into memory
	memcpy(ptr1, m_cameraUbo.cameraData, sizeof(PerFrameCameraData));
	// make sure to tell OpenGL we're done with the pointer
	glUnmapBuffer(GL_UNIFORM_BUFFER);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);


	if (m_lightUbo.bufferHandle != 0)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_lightUbo.bufferHandle);
		// get pointer
		void* ptr2 = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
		// now copy data into memory
		memcpy(ptr2, m_lightUbo.lightData, m_lightUbo.lightCount * sizeof(PerframePhongLightData));
		// make sure to tell OpenGL we're done with the pointer
		glUnmapBuffer(GL_UNIFORM_BUFFER);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}
