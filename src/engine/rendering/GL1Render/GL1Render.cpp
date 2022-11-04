#include "GL1Render.h"

#include "../Object.h"
#include "../Mesh.h"

#include <algorithm>
#include <stdexcept>

GL1Render::GL1Render()
{
	m_objects.reserve(1000);
}

GL1Render::~GL1Render()
{
	
}

void GL1Render::init()
{
	int glewState = glewInit();
	if (!glewState)
		throw std::runtime_error("Error initializing glew");
}

void GL1Render::setupObject(Object* object)
{
	m_objects.push_back(object);
}

void GL1Render::removeObject(Object* object)
{

}

void GL1Render::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::for_each(m_objects.begin(), m_objects.end(), [](Object* object) {
		object->computeModelMatrix();
		auto meshes = object->getMesh();
		for (auto mesh : meshes)
		{
			auto& meshVertices = mesh->getVerticesList();

			for (u32 triangleIndex = 0; triangleIndex < meshVertices.size(); triangleIndex += 3)
			{
				glBegin(GL_TRIANGLES);
				{
					for (u32 i = triangleIndex; i < (triangleIndex + 3); i++)
					{
						//glColor3f(meshVertices[i].color.r, meshVertices[i].color.g, meshVertices[i].color.b);
						auto pos = meshVertices[i].pos;
						auto fpos = object->getModelMatrix() * glm::vec4(pos.x, pos.y, pos.z, 1.0f);
						glVertex3f(fpos.x, fpos.y, fpos.z);
					}
				}
				glEnd();
			}
		}
	});
}

void GL1Render::setCameraUniformBuffer(std::string name, PerFrameCameraData* data)
{

}

void GL1Render::setPhongLightUniformBuffer(std::string name, const std::vector<PerframePhongLightData>& data)
{

}
