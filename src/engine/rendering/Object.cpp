#include "Object.h"

#include "Material.h"
#include "Mesh.h"

void Object::addShadersToMaterials(const std::vector<std::string>& shaderPath) const
{
	auto material = m_meshes[0]->getMaterial();
	material->addShaders(shaderPath);
	auto renderProgram = material->getRenderProgram();
	for (u32 i = 1; i < m_meshes.size(); i++)
	{
		m_meshes[i]->getMaterial()->setRenderProgram(renderProgram);
	}
}
