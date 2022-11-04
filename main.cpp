#include "src/engine/core/System.h"
#include "src/engine/rendering/OrbitalLight.h"

#include <iostream>
#include <memory>

#include "src/scene/TriangleRot.h"
#include "src/scene/TriangleRotTex.h"
#include "src/scene/CubeIndices.h"
#include "src/scene/CubeTex.h"
#include "src/scene/AsianTown.h"
#include "src/scene/Bunny.h"

int main(int argc, char** argv)
{
	WindowParameters parameters;
	parameters.name = "Engine";
	parameters.width = 1280;
	parameters.height = 720;
	parameters.majorVersion = 4;
	parameters.minorVersion = 3;
	parameters.resizable = 0;

	// General System
	System system{ parameters, RendererType::GL4Render };
	system.setCamera(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1), ProjectionType::PERSPECTIVE, CameraType::FLY);
	
	// Scene object
	Bunny bunny{ system };

	// Lighting settings
	glm::vec3 ambient(1.0f, 1.0f, 1.0f);
	f32 ambientStrengh{ 0.3f };
	f32 specularStrengh{ 0.5f };
	f32 kAtt{ 1.0f };
	f32 lAtt{ 0.2f };
	f32 qAtt{ 0.03f };

	system.addLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f), ambient, ambientStrengh, specularStrengh, kAtt, lAtt, qAtt, glm::vec3(1, 1, 1), LightType::DIRECTIONAL);
	system.addLight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.0f, 0.02f, 0.6f, 1.0f), ambient, ambientStrengh, specularStrengh, kAtt, lAtt, qAtt, glm::vec3(1, 1, 1), LightType::POINT);
	system.addLight(glm::vec3(1.0f, 0.0f, -1.0f), glm::vec4(0.0f, 0.6f, 0.02f, 1.0f), ambient, ambientStrengh, specularStrengh, kAtt, lAtt, qAtt, glm::vec3(1, 1, 1), LightType::POINT);
	system.addLight(glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec4(0.15f, 0.2f, 0.6f, 1.0f), ambient, ambientStrengh, specularStrengh, kAtt, lAtt, qAtt, glm::vec3(1, 1, 1), LightType::POINT);

	std::unique_ptr<OrbitalLight> orbitalLight = std::make_unique<OrbitalLight>(bunny.getPosition(), glm::vec3(0, 0, 5), glm::vec4(1.0f, 0.1f, 0.1f, 1.0f), ambient, ambientStrengh, specularStrengh, kAtt, lAtt, qAtt);
	orbitalLight->setRotationSpeed(1.5f);
	orbitalLight->setRotationAxis(glm::vec3(0, 1, 0));
	system.addLight(std::move(orbitalLight), true);
	
	// Main loop (update Time, objects, input and draw objects)
	system.run();
}

