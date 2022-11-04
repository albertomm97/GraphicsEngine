#pragma once

#include "../../core/common/Types.h"

struct Vertex;

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(const void* vertices, size_t size);
	~VertexBuffer();

	void bind() const;
	void unbind() const;
private:
	u32 m_handle;
};

