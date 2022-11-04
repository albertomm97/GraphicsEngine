#include "System.h"
#include "../rendering/FactoryEngine.h"
#include "../rendering/Object.h"
#include "../rendering/Render.h"
#include "../rendering/Material.h"
#include "../rendering/Light.h"
#include "input/InputManager.h"
#include "../rendering/CameraKeyboard.h"
#include "../rendering/CameraFly.h"
#include "../rendering/CameraFPS.h"
#include "Time.h"

#include <GLFW/glfw3.h>
#include <pugixml.hpp>

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

System::System(WindowParameters& parameters, RendererType desiredRenderer = RendererType::GL4Render)
{
	m_objects = std::vector<Object*>();
	m_objects.reserve(1000);
	
	m_window = std::make_unique<Window>(parameters);

	m_factory = std::make_unique<FactoryEngine>();
	
	m_renderer = m_factory->getNewRenderer(desiredRenderer);

	InputManager::init(m_window->get());
}

System::~System()
{
	
}

void System::addObject(Object* object)
{
	m_renderer->setupObject(object);
	m_objects.push_back(object);
}

void System::exit()
{
	m_end = true;
}

void System::run()
{
	while (!m_end)
	{
		Time::update();

		// Check Input and window closing event
		if (InputManager::isPressed(GLFW_KEY_E) || m_window->windowShouldClose())
			m_end = true;

		// Update camera and per frame camera data
		m_camera->update();
		m_perFrameData.cameraPosition = m_camera->getPosition();
		m_perFrameData.projectionMatrix = m_camera->getProjection();
		m_perFrameData.viewMatrix = m_camera->getView();

		// Update lights entity object and per frame light data
		for (u32 i = 0; i < m_lights.size(); i++)
		{
			m_lights[i]->update();
			m_lights[i]->updatePerFrameData(m_perFrameLights[i]);
		}
		
		// Update Objects
		std::for_each(m_objects.begin(), m_objects.end(), [](Object* object) {
			object->update();
			object->computeModelMatrix();
		});

		// Draw Objects
		m_renderer->draw();

		// Pool events and swap buffers
		m_window->poolEvents();
		m_window->swapBuffers();
	}
}


void System::setNewRenderer(RendererType desiredRenderer)
{
	if (m_renderer != nullptr)
		m_renderer.reset();

	m_renderer = m_factory->getNewRenderer(desiredRenderer);
}

void System::setCamera(glm::vec3 position, 
					   glm::vec3 up, 
					   glm::vec3 lookAt, 
					   ProjectionType projection, 
					   CameraType type)
{
	auto windowExtent = m_window->getWindowExtent();
	glfwSetInputMode(m_window->get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	if (type == CameraType::KEYBOARD)
	{
		m_camera = std::make_unique<CameraKeyboard>(position, up, lookAt, windowExtent, projection);
	}
	else if (type == CameraType::FPS)
	{
		m_camera = std::make_unique<CameraFPS>(position, up, lookAt, windowExtent, projection);
	}
	else if (type == CameraType::FLY)
	{
		m_camera = std::make_unique<CameraFly>(position, up, lookAt, windowExtent, projection);
	}

	m_perFrameData.cameraPosition = m_camera->getPosition();
	m_perFrameData.projectionMatrix = m_camera->getProjection();
	m_perFrameData.viewMatrix = m_camera->getView();

	m_renderer->setCameraUniformBuffer(std::string("Camera"), &m_perFrameData);
}

void System::addLight(glm::vec3 position, glm::vec4 color, LightType type, bool lastLight)
{
	m_lights.push_back(std::make_unique<Light>(position, color, type));
	m_perFrameLights.emplace_back(position, color, glm::vec3(1.0f, 1.0f, 1.0f), 0.4f, 0.5f);
	if (lastLight)
		m_renderer->setPhongLightUniformBuffer(std::string("Light"), m_perFrameLights);
}

void System::addLight(std::unique_ptr<Light> light, bool lastLight)
{
	m_perFrameLights.emplace_back(light->getPosition(), light->getColor(), light->getAmbient(), light->getAmbientStrengh(), light->getSpecularStrengh(), light->getConstAttenuation(), light->getLinearAttenuation(), light->getQuadraticAttenuation(), light->getDirection(), static_cast<i32>(light->getLightType()));
	m_lights.push_back(std::move(light));
	
	if (lastLight)
		m_renderer->setPhongLightUniformBuffer(std::string("Light"), m_perFrameLights);
}

void System::addLight(glm::vec3 position, glm::vec4 color, glm::vec3 ambient, f32 ambientStrengh, f32 specularStrengh, f32 kAttenuation, f32 lAttenuation, f32 qAttenuation, glm::vec3 direction, LightType type, bool lastLight)
{
	m_lights.push_back(std::make_unique<Light>(position, color, ambient, ambientStrengh, specularStrengh, kAttenuation, lAttenuation, qAttenuation, direction, type));
	m_perFrameLights.emplace_back(position, color, ambient, ambientStrengh, specularStrengh, kAttenuation, lAttenuation, qAttenuation, direction, static_cast<i32>(type));
	if (lastLight)
		m_renderer->setPhongLightUniformBuffer(std::string("Light"), m_perFrameLights);
}

std::shared_ptr<Material> System::createNewMaterial(std::string name, std::vector<std::string>& shadersPath)
{
	if (m_materials.find(name) == m_materials.end())
	{
		auto material = m_factory->getNewMaterial(shadersPath);
		m_materials[name] = material;
		return material;
	}
	else
		return m_materials[name];
}

std::shared_ptr<Material> System::createRawMaterial(std::string name)
{
	if (m_materials.find(name) == m_materials.end())
	{
		auto material = m_factory->getNewRawMaterial();
		m_materials[name] = material;
		return material;
	}
	else
		return m_materials[name];
}

std::shared_ptr<Material> System::createNewMaterialFromRenderProgram(std::string name, std::shared_ptr<RenderProgram> renderProgram)
{
	if (m_materials.find(name) == m_materials.end())
	{
		auto material = m_factory->getNewRawMaterial();
		material->setRenderProgram(renderProgram);
		m_materials[name] = material;
		return material;
	}
	else
		return m_materials[name];
}

std::shared_ptr<Texture> System::createNewTexture(std::string name, const std::string& path)
{
	if (m_textures.find(name) == m_textures.end())
	{
		auto texture = m_factory->getNewTexture(path);
		m_textures[name] = texture;
		return texture;
	}
	else
		return m_textures[name];
}

template <typename T>
std::vector<T> splitString(const std::string& str, char delim) 
{
	std::vector<T> elems = std::vector<T>();
	std::stringstream sstream(str);
	std::string item;
	T tipoDato;
	if (str != "") {
		while (std::getline(sstream, item, delim))
		{
			std::istringstream str(item);
			str >> tipoDato;
			elems.push_back(tipoDato);
		}
	}
	return elems;
}

void System::loadMeshFromFile(const std::string& path, Object* object)
{
	pugi::xml_document doc;
	pugi::xml_parse_result res = doc.load_file(path.c_str());
	if (res) 
	{
		pugi::xml_node meshNode = doc.child("mesh");
		pugi::xml_node buffersNode = meshNode.child("buffers");
	
		std::vector<std::shared_ptr<Mesh>> meshes;

		for (pugi::xml_node bufferNode = buffersNode.child("buffer");
			bufferNode;
			bufferNode = bufferNode.next_sibling("buffer")) 
		{
			auto mesh = std::make_shared<Mesh>();
			std::vector<Vertex> vertices;
			auto material = createRawMaterial(std::string("matMesh" + std::to_string(mesh->getId())));
			std::string texPath(bufferNode.child("material").child("texture").text().as_string());
			std::shared_ptr<Texture> texture;
			if (texPath != "")
			{
				texture = createNewTexture(std::string("texMesh" + std::to_string(mesh->getId())), texPath);
				material->setTexture(texture);
			}

			if (std::string(bufferNode.child("material").child("color").text().as_string()) != "")
			{
				auto color = splitString<f32>(bufferNode.child("material").child("color").text().as_string(), ',');
				material->setColor(glm::vec4(color[0], color[1], color[2], color[3]));
			}

			if (std::string(bufferNode.child("material").child("shininess").text().as_string()) != "")
			{
				i32 shininess = bufferNode.child("material").child("shininess").text().as_int();
				material->setShininess(shininess);
			}
				
			mesh->setMaterial(material);

			auto indices = splitString<u32>(bufferNode.child("indices").text().as_string(), ',');
			mesh->addIndices(indices);

			std::vector<f32> coords = splitString<f32>(bufferNode.child("coords").text().as_string(), ',');
			std::vector<f32> texCoords = splitString<f32>(bufferNode.child("texCoords").text().as_string(), ',');
			auto itCoord = coords.begin();
			auto itText = texCoords.begin();
			int numVertCompCount = bufferNode.child("coords").attribute("vertexCompCount").as_int();
			int numTextCompCount = bufferNode.child("texCoords").attribute("texCoordCompCount").as_int();

			vertices.reserve(coords.size() / numVertCompCount);

			if (coords.size() / numVertCompCount == texCoords.size() / numTextCompCount)
			{
				while (itCoord != coords.end() && itText != texCoords.end())
				{
					Vertex vert;
					vert.pos.x = *itCoord; itCoord++;
					vert.pos.y = *itCoord; itCoord++;
					vert.pos.z = *itCoord; itCoord++;

					/*vert.texCoords.x = *itText; itText++;
					vert.texCoords.y = *itText; itText++;*/

					vertices.push_back(vert);
				}
			}
			else {
				std::cout << "error: numero de componentes en fichero no concuerda\n";
			}
			mesh->AddVertices(vertices);
			meshes.push_back(mesh);
		}
		object->setMeshesFromVector(meshes);
	}
	else
		std::cout << "ERROR carga de datos: " << res.description();
}

void System::loadMeshFromFileNormal(const std::string& path, Object* object)
{
	pugi::xml_document doc;
	pugi::xml_parse_result res = doc.load_file(path.c_str());
	if (res)
	{
		pugi::xml_node meshNode = doc.child("mesh");
		pugi::xml_node buffersNode = meshNode.child("buffers");

		std::vector<std::shared_ptr<Mesh>> meshes;

		for (pugi::xml_node bufferNode = buffersNode.child("buffer");
			bufferNode;
			bufferNode = bufferNode.next_sibling("buffer"))
		{
			auto mesh = std::make_shared<Mesh>();
			std::vector<Vertex> vertices;
			auto material = createRawMaterial(std::string("matMesh" + std::to_string(mesh->getId())));
			std::string texPath(bufferNode.child("material").child("texture").text().as_string());
			std::shared_ptr<Texture> texture;
			if (texPath != "")
			{
				texture = createNewTexture(std::string("texMesh" + std::to_string(mesh->getId())), texPath);
				material->setTexture(texture);
			}

			if (std::string(bufferNode.child("material").child("color").text().as_string()) != "")
			{
				auto color = splitString<f32>(bufferNode.child("material").child("color").text().as_string(), ',');
				glm::vec4 objectColor = glm::vec4(color[0], color[1], color[2], color[3]);
				material->setColor(objectColor);
			}

			if (std::string(bufferNode.child("material").child("shininess").text().as_string()) != "")
			{
				i32 shininess = bufferNode.child("material").child("shininess").text().as_int();
				material->setShininess(shininess);
			}

			mesh->setMaterial(material);

			auto indices = splitString<u32>(bufferNode.child("indices").text().as_string(), ',');
			mesh->addIndices(indices);

			std::vector<f32> coords = splitString<f32>(bufferNode.child("coords").text().as_string(), ',');
			std::vector<f32> texCoords = splitString<f32>(bufferNode.child("texCoords").text().as_string(), ',');
			std::vector<f32> normals = splitString<f32>(bufferNode.child("normals").text().as_string(), ',');
			auto itCoord = coords.begin();
			auto itText = texCoords.begin();
			auto itNorm = normals.begin();

			int numVertCompCount = bufferNode.child("coords").attribute("vertexCompCount").as_int();
			int numTextCompCount = bufferNode.child("texCoords").attribute("texCoordCompCount").as_int();
			int numNormalCompCount = bufferNode.child("normals").attribute("normalCompCount").as_int();

			vertices.reserve(coords.size() / numVertCompCount);

			//if (coords.size() % numVertCompCount == 0 /*== texCoords.size() / numTextCompCount*/)
			//{
				while (itCoord != coords.end() /*&& itText != texCoords.end()*/ &&
					itNorm != normals.end())
				{
					Vertex vert;
					vert.pos.x = *itCoord; itCoord++;
					vert.pos.y = *itCoord; itCoord++;
					vert.pos.z = *itCoord; itCoord++;

					//vert.texCoords.x = *itText; itText++;
					//vert.texCoords.y = *itText; itText++;

					vert.normals.x = *itNorm; itNorm++;
					vert.normals.y = *itNorm; itNorm++;
					vert.normals.z = *itNorm; itNorm++;

					vertices.push_back(vert);
				}
			//}
			//else {
				//std::cout << "error: numero de componentes en fichero no concuerda\n";
			//}
			mesh->AddVertices(vertices);
			meshes.push_back(mesh);
		}
		object->setMeshesFromVector(meshes);
	}
	else
		std::cout << "ERROR carga de datos: " << res.description();
}
