#pragma once

#include <memory>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "../Material.h"
#include "../RenderProgram.h"

enum class DrawType
{
	DEFAULT,
	INDICES,
	INSTANCED
};

class Object;

struct RenderInfo
{
	RenderInfo(std::unique_ptr<VertexArray> vao, std::shared_ptr<Material> mat, u32 numVertices, Object* object)
		: vao{ std::move(vao) }, vbo{}, ib{}, material{ mat }, count{ numVertices }, object{ object }, drawType{ DrawType::DEFAULT } {}

	RenderInfo(std::unique_ptr<VertexArray> vao, std::unique_ptr<VertexBuffer> vbo, std::shared_ptr<Material> mat, u32 numVertices, Object* object)
		: vao{ std::move(vao) }, vbo{ std::move(vbo) }, ib{}, material{ mat }, count{ numVertices }, object{ object }, drawType{ DrawType::DEFAULT } {}

	RenderInfo(std::unique_ptr<VertexArray> vao, std::unique_ptr<VertexBuffer> vbo, std::unique_ptr<IndexBuffer> ib, std::shared_ptr<Material> mat, u32 numIndices, Object* object)
		: vao{ std::move(vao) }, vbo{ std::move(vbo) }, ib{ std::move(ib)}, material{ mat }, count{ numIndices }, object{ object }, drawType{ DrawType::INDICES }  {}


	void prepareForRender()
	{
		material->getRenderProgram()->use();

		if (material->getTexture())
		{
			material->getTexture()->bind();
		}

		vao->bind();
	}

	std::unique_ptr<VertexArray> vao;
	std::unique_ptr<VertexBuffer> vbo;
	std::unique_ptr<IndexBuffer> ib;
	std::shared_ptr<Material> material;
	u32 count;
	Object* object;
	DrawType drawType;
};