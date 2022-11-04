#pragma once

#include "../core/common/Types.h"
#include "Vertex.h"

#include <vector>
#include <memory>

class Material;

class Mesh
{
public:
	Mesh() = default;

	u32 getMeshId() const;

	void addVertex(Vertex vertex);
	
	void AddVertices(std::vector<Vertex>& vertices);
	
	void addIndex(u32 index);
	void addIndices(std::vector<u32>& indices);
	
	std::vector<Vertex>& getVerticesList();
	
	std::vector<u32>& getIndicesList();
	inline u32 getId() const { return m_id; }

	std::shared_ptr<Material> getMaterial() const;
	void setMaterial(std::shared_ptr<Material> material);

private:
	static u32 id_gen;
	u32 m_id{ id_gen++ };

	// Different types of vertex attribute
	std::vector<Vertex> m_vertList{};
	
	std::vector<u32> m_indicesList{};
	std::shared_ptr<Material> m_material{};
};

