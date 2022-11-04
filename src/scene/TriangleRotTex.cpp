#include "TriangleRotTex.h"

#include "../engine/core/Time.h"
#include "../engine/core/input/InputManager.h"
#include "../engine/core/System.h"
#include "../engine/rendering/Mesh.h"
#include "../engine/rendering/Material.h"

TriangleRotTex::TriangleRotTex(System& system)
	: m_system{ system }
{
	std::vector<std::string> basicTexShadersPath{
		"data/shaders/basictex.vert",
		"data/shaders/basictex.frag"
	};

	auto material = m_system.createNewMaterial("triangle_tex", basicTexShadersPath);
	auto texture = m_system.createNewTexture(std::string("wall"), "data/textures/wall.jpg");
	material->setTexture(texture);

	auto mesh = std::make_shared<Mesh>();

	/*mesh->addVertex(VertexPCT{ glm::vec3(-0.5f, -0.5, 0.0f), glm::vec4(0.0, 1.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f) });
	mesh->addVertex(VertexPCT{ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) });
	mesh->addVertex(VertexPCT{ glm::vec3(0.0, 0.5, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f) });*/
	mesh->setMaterial(material);

	setPosition(glm::vec3(0, 0, 0));
	setScaleFactor(glm::vec3(1.5f, 1.5, 1.5f));
	setMesh(mesh);

	m_system.addObject(this);
}

void TriangleRotTex::update()
{
}
