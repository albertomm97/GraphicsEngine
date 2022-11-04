#pragma once

#include "Entity.h"

#include <string>
#include <memory>

class Mesh;

class Object : public Entity
{
public:
	Object() = default;
	virtual ~Object() override = default;

	inline const std::vector<std::shared_ptr<Mesh>>& getMesh() const { return m_meshes; }
	inline void setMesh(std::shared_ptr<Mesh> mesh) { m_meshes.push_back(mesh); }
	inline void setMeshesFromVector(std::vector<std::shared_ptr<Mesh>>& meshes) { m_meshes = std::move(meshes); }
	
	void addShadersToMaterials(const std::vector<std::string>& shaderPath) const;
	virtual void update() override {};

protected:
	std::vector<std::shared_ptr<Mesh>> m_meshes;
};

