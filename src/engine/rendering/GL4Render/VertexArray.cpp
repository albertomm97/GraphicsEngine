#include "VertexArray.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <iostream>


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_handle);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_handle);
}

void VertexArray::bind() const
{
	glBindVertexArray(m_handle);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}
