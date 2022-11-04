#include "CubeTexLight.h"

#include "../engine/core/Time.h"
#include "../engine/core/input/InputManager.h"
#include "../engine/core/System.h"

#include "../engine/rendering/Mesh.h"
#include "../engine/rendering/Material.h"


CubeTexLight::CubeTexLight(System& system)
	: m_system{ system }
{
	std::vector<std::string> cubeTexShaderPath{
		"data/shaders/cubetex.vert",
		"data/shaders/cubetex.frag"
	};

	// F

	setPosition(glm::vec3(0, 0, 0));
	setScaleFactor(glm::vec3(1.0f, 1.0f, 1.0f));

	m_system.addObject(this);
}

void CubeTexLight::update()
{

}

