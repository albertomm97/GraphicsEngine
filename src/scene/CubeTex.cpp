#include "CubeTex.h"

#include "../engine/core/Time.h"
#include "../engine/core/input/InputManager.h"
#include "../engine/core/System.h"

#include "../engine/rendering/Mesh.h"
#include "../engine/rendering/Material.h"


CubeTex::CubeTex(System& system)
	: m_system { system }
{
	std::vector<std::string> cubeTexShaderPath{
		"data/shaders/asiantown.vert",
		"data/shaders/asiantown.frag"
	};

	auto frontMaterial= m_system.createNewMaterial("cubetext", cubeTexShaderPath);
	auto frontTexture = m_system.createNewTexture(std::string("front"), "data/textures/front.png");
	frontMaterial->setTexture(frontTexture);

	///* Sides
	auto sidemesh = std::make_shared<Mesh>();
	/*sidemesh->addVertex(Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 0.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f) });

	sidemesh->addVertex(Vertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3( 0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3( 0.5f,  0.5f, 0.5f), glm::vec2(1.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3( 0.5f,  0.5f, 0.5f), glm::vec2(1.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(0.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f) });

	sidemesh->addVertex(Vertex{ glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(1.0f, 0.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(-0.5f,  0.5f, 0.5f), glm::vec2(1.0f, 0.0f) });

	sidemesh->addVertex(Vertex{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f) });
	sidemesh->addVertex(Vertex{ glm::vec3(0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f) });*/

	sidemesh->setMaterial(frontMaterial);
	setMesh(sidemesh);

	// Top and bottom
	auto topMaterial = m_system.createNewMaterialFromRenderProgram(std::string("top"), frontMaterial->getRenderProgram());
	auto topTexture = m_system.createNewTexture(std::string("toptex"), "data/textures/top.png");
	topMaterial->setTexture(topTexture);

	auto topbottomesh = std::make_shared<Mesh>();
	/*topbottomesh->addVertex(Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) });
	topbottomesh->addVertex(Vertex{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f) });
	topbottomesh->addVertex(Vertex{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f) });
	topbottomesh->addVertex(Vertex{ glm::vec3(0.5f, -0.5f,  0.5f), glm::vec2(1.0f, 0.0f) });
	topbottomesh->addVertex(Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f) });
	topbottomesh->addVertex(Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) });

	topbottomesh->addVertex(Vertex{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f) });
	topbottomesh->addVertex(Vertex{ glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f) });
	topbottomesh->addVertex(Vertex{ glm::vec3(0.5f, 0.5f,  0.5f), glm::vec2(1.0f, 0.0f) });
	topbottomesh->addVertex(Vertex{ glm::vec3(0.5f, 0.5f,  0.5f), glm::vec2(1.0f, 0.0f) });
	topbottomesh->addVertex(Vertex{ glm::vec3(-0.5f, 0.5f,  0.5f), glm::vec2(0.0f, 0.0f) });
	topbottomesh->addVertex(Vertex{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f) });*/
	
	topbottomesh->setMaterial(topMaterial);
	setMesh(topbottomesh);
	
	setPosition(glm::vec3(0, 0, 0));
	setScaleFactor(glm::vec3(1.0f, 1.0f, 1.0f));

	m_system.addObject(this);
}

void CubeTex::update()
{

}
