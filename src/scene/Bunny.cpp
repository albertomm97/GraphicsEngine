#include "Bunny.h"

#include "../engine/core/Time.h"
#include "../engine/core/input/InputManager.h"
#include "../engine/core/System.h"
#include "../engine/rendering/OrbitalLight.h"
#include "../engine/rendering/Mesh.h"
#include "../engine/rendering/Material.h"

Bunny::Bunny(System& system)
	: m_system{ system }
{
	std::vector<std::string> cubeTextnormalsPath{
		"data/shaders/cubetextnormals.vert",
		"data/shaders/cubetextnormals.frag"
	};

	m_system.loadMeshFromFileNormal("data/meshes/bunny.msh", this);
	addShadersToMaterials(cubeTextnormalsPath);

	setPosition(glm::vec3(0, 0, -1));
	setRotation(glm::vec3(90, 0, 0));
	setScaleFactor(glm::vec3(1.0f, 1.0f, 1.0f));

	m_system.addObject(this);
}

void Bunny::update()
{
	
}

