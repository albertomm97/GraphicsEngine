#include "Mesh.h"

#include "Material.h"

u32 Mesh::id_gen = 0;

u32 Mesh::getMeshId() const
{
    return m_id;
}


void Mesh::addVertex(Vertex vertex)
{
    m_vertList.push_back(vertex);
}


void Mesh::AddVertices(std::vector<Vertex>& vertices)
{
    m_vertList = std::move(vertices);
}

void Mesh::addIndex(u32 index)
{
    m_indicesList.push_back(index);
}

void Mesh::addIndices(std::vector<u32>& indices)
{
    m_indicesList = std::move(indices);
}

std::vector<Vertex>& Mesh::getVerticesList()
{
    return m_vertList;
}

std::vector<u32>& Mesh::getIndicesList()
{
    return m_indicesList;
}

std::shared_ptr<Material> Mesh::getMaterial() const 
{ 
    return m_material; 
}

void Mesh::setMaterial(std::shared_ptr<Material> material)
{ 
    m_material = material; 
}
