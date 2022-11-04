#include "GLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <iostream>

void GLTexture::loadTexture(const std::string& path)
{
	glGenTextures(1, &m_handle);
	glBindTexture(GL_TEXTURE_2D, m_handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	
	unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, nullptr, 4);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Texture created succesfully!\n";
	}
	else
	{
		std::cout << "Failed to load texture\n";
	}
	stbi_image_free(data);
}

u32 GLTexture::getHandle()
{
	return m_handle;
}

glm::ivec2 GLTexture::getSize()
{
	return glm::ivec2(m_width, m_height);
}

void GLTexture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_handle);
}
