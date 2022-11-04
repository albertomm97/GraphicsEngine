#include "TriangleRot.h"

#include "../engine/core/Time.h"
#include "../engine/core/input/InputManager.h"
#include "../engine/core/System.h"

#include "../engine/rendering/Mesh.h"
#include "../engine/rendering/Material.h"

#include <iostream>

TriangleRot::TriangleRot(System& system)
	: m_system{ system }
{
	std::vector<std::string> basicShadersPath{
		"data/shaders/basic.vert",
		"data/shaders/basic.frag"
	};

	auto material = m_system.createNewMaterial("triangle_rot", basicShadersPath);

	auto mesh = std::make_shared<Mesh>();
	mesh->addVertex(Vertex{ glm::vec3(-0.5f, -0.5, 0.0f), glm::vec4(0.0, 1.0f, 0.0f, 1.0f) });
	mesh->addVertex(Vertex{ glm::vec3(0.0f, 0.5f, 0.0f), glm::vec4(0.0f, 0.0f, 1.0f, 1.0f) });
	mesh->addVertex(Vertex{ glm::vec3(0.5, -0.5, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) });
	mesh->setMaterial(material);

	setPosition(glm::vec3(0, 0, -1));
	setScaleFactor(glm::vec3(0.5f, 0.5, 0.5f));
	setMesh(mesh);

	m_system.addObject(this);
}

void TriangleRot::update()
{
	if (InputManager::isPressed('D'))
	{
		//m_position.x += 1.0f * Time::deltaTime;
	}
		
	if (InputManager::isPressed('A'))
	{
		//m_position.x -= 1.0f * Time::deltaTime;
	}
			
	m_rotation.y += 1.0f * Time::deltaTime;
}
