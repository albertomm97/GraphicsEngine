#include "CubeIndices.h"

#include "../engine/core/Time.h"
#include "../engine/core/input/InputManager.h"
#include "../engine/core/System.h"

#include "../engine/rendering/Mesh.h"
#include "../engine/rendering/Material.h"


CubeIndices::CubeIndices(System& system)
    : m_system{ system }
{
	std::vector<std::string> basicTexShadersPath{
		"data/shaders/cubebasic.vert",
		"data/shaders/cubebasic.frag"
	};

	auto material = m_system.createNewMaterial("cubeindices", basicTexShadersPath);
	auto mesh = std::make_shared<Mesh>();
	/*mesh->addVertex(Vertex{ glm::vec3(0.5f, 0.5, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) });
	mesh->addVertex(Vertex{ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) });
	mesh->addVertex(Vertex{ glm::vec3(-0.5, -0.5, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) });
	mesh->addVertex(Vertex{ glm::vec3(-0.5, 0.5, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) });*/
	std::vector<u32> indices{ 0, 1, 3, 1, 2 };
	mesh->addIndices(indices);

	mesh->setMaterial(material);

	setMesh(mesh);

	setPosition(glm::vec3(0, 0, 0));
	setScaleFactor(glm::vec3(0.5f, 0.5, 0.5f));

	m_system.addObject(this);
}

void CubeIndices::update()
{
}
