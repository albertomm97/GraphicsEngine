#include "AsianTown.h"

#include "../engine/core/Time.h"
#include "../engine/core/input/InputManager.h"
#include "../engine/core/System.h"

#include "../engine/rendering/Mesh.h"
#include "../engine/rendering/Material.h"


AsianTown::AsianTown(System& system)
	: m_system{ system }
{
	std::vector<std::string> asianTownShaders{
		"data/shaders/asiantown.vert",
		"data/shaders/asiantown.frag"
	};

	m_system.loadMeshFromFile("data/meshes/asian_town.msh", this);
	addShadersToMaterials(asianTownShaders);

	setPosition(glm::vec3(0, 0, 0));
	setScaleFactor(glm::vec3(1.0f, 1.0f, 1.0f));

	m_system.addObject(this);
}

void AsianTown::update()
{

}