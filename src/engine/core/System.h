#pragma once

#include "../core/common/Types.h"
#include "../rendering/Mesh.h"
#include "../rendering/Camera.h"
#include "../rendering/Render.h"
#include "../rendering/Light.h"
#include "Window.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <map>

class Object;
class Render;
class InputManager;
class FactoryEngine;
class Material;
class Texture;
class RenderProgram;
class Light;

struct PerFrameCameraData;
struct PerframePhongLightData;

class System
{
public:
	explicit System(WindowParameters& parameters, RendererType desiredRenderer);
	~System();

	void addObject(Object* object);
	void exit();
	void run();

	void setNewRenderer(RendererType desiredRenderer);
	void setCamera(glm::vec3 position, glm::vec3 up, glm::vec3 lookAt, ProjectionType projection = ProjectionType::PERSPECTIVE, CameraType type = CameraType::FLY);
	void addLight(glm::vec3 position, glm::vec4 color, LightType type, bool lastLight = false);
	void addLight(glm::vec3 position, glm::vec4 color, glm::vec3 ambient, f32 ambientStrengh, f32 specularStrengh, f32 kAttenuation, f32 lAttenuation, f32 qAttenuation, glm::vec3 direction, LightType type, bool lastLight = false);
	void addLight(std::unique_ptr<Light> light, bool lastLight = false);

	std::shared_ptr<Material> createNewMaterial(std::string name, std::vector<std::string>& shadersPath);
	std::shared_ptr<Material> createRawMaterial(std::string name);
	std::shared_ptr<Material> createNewMaterialFromRenderProgram(std::string name, std::shared_ptr<RenderProgram> renderProgram);

	std::shared_ptr<Texture> createNewTexture(std::string name, const std::string& path);

	void loadMeshFromFile(const std::string& path, Object* object);
	void loadMeshFromFileNormal(const std::string& path, Object* object);

private:
	std::unique_ptr<FactoryEngine> m_factory;
	std::unique_ptr<Render> m_renderer;
	std::unique_ptr<Window> m_window;
	std::unique_ptr<Camera> m_camera;
	std::vector<Object*> m_objects;
	std::unordered_map<std::string, std::shared_ptr<Material>> m_materials; // create ResourceManager 
	std::map<std::string, std::shared_ptr<Texture>> m_textures; // create ResourceManager 
	std::vector<std::unique_ptr<Light>> m_lights;
	PerFrameCameraData m_perFrameData;
	std::vector<PerframePhongLightData> m_perFrameLights;

	bool m_end;
};

