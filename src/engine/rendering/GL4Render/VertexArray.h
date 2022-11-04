#pragma once

#include "../../core/common/Types.h"

class VertexArray
{
public:
	explicit VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;

private:
	u32 m_handle;
};

