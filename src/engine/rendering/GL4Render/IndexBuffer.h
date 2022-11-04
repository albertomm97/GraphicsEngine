#pragma once

#include "../../core/common/Types.h"

class IndexBuffer
{
public:
	IndexBuffer() = default;
	explicit IndexBuffer(const void* indices, u32 size);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

private:
	u32 m_handle;
};

