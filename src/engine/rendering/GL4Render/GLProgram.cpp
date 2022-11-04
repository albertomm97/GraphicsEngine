#include "GLProgram.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

GLProgram::~GLProgram()
{
	glDeleteProgram(m_handle);
}

void GLProgram::addShader(const std::string& path, ShaderType type)
{
	if (m_shaderHandles.find(type) != m_shaderHandles.end())
		return;

	std::string vertexCode;
	std::ifstream vShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(path.c_str());
		std::stringstream vShaderStream;
		// read file'm_shaderHandles buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		std::cout << vertexCode << "\n";
	}
	catch (std::ifstream::failure e)
	{
		std::cout<< e.what() << "\n";
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
	const char* code = vertexCode.c_str();

	auto desiredShaderType = GL_VERTEX_SHADER;
	switch (type)
	{
		case ShaderType::VERTEX:
			desiredShaderType = GL_VERTEX_SHADER;
			break;
		case ShaderType::FRAG:
			desiredShaderType = GL_FRAGMENT_SHADER;
			break;
		case ShaderType::GEOMETRY:
			desiredShaderType = GL_GEOMETRY_SHADER;
			break;
		case ShaderType::TESSEV:
			desiredShaderType = GL_TESS_EVALUATION_SHADER;
			break;
		case ShaderType::TESSCONTROL:
			desiredShaderType = GL_TESS_CONTROL_SHADER;
			break;
		case ShaderType::COMPUTE:
			desiredShaderType = GL_COMPUTE_SHADER;
			break;
	}

	auto handle = glCreateShader(desiredShaderType);

	glShaderSource(handle, 1, &code, nullptr);
	glCompileShader(handle);

	int success;
	char infoLog[512];
	glGetShaderiv(handle, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(handle, 512, NULL, infoLog);
		std::cerr << infoLog << "\n";
	}

	m_shaderHandles[type] = handle;
}

void GLProgram::link()
{
	if (m_linked)
		return;

	checkHandleValue();

	for (auto& shader : m_shaderHandles)
	{
		glAttachShader(m_handle, shader.second);
	}

	glLinkProgram(m_handle);
	m_linked = linkedCorrectly();
	
	for (auto& shader : m_shaderHandles)
	{
		glDeleteShader(shader.second);
	}
}

void GLProgram::use() const
{
	if (m_linked)
	{
		glUseProgram(m_handle);
	}
}

u32 GLProgram::getHandle() const
{
	return m_handle;
}

void GLProgram::setUniformVec2(const std::string& name, const glm::vec2& v)
{
	if (!correctUniformName(name))
		return;

	glUniform2fv(m_uniformLocations[name], 1, glm::value_ptr(v));
}

void GLProgram::setUniformVec3(const std::string& name, const glm::vec3& v)
{
	if (!correctUniformName(name))
		return;

	glUniform3fv(m_uniformLocations[name], 1, glm::value_ptr(v));
}

void GLProgram::setUniformVec4(const std::string& name, const glm::vec4& v)
{
	if (!correctUniformName(name))
		return;

	glUniform4fv(m_uniformLocations[name], 1, glm::value_ptr(v));
}

void GLProgram::setUniformMat4(const std::string& name, const glm::mat4& m)
{
	if (!correctUniformName(name))
		return;

	glUniformMatrix4fv(m_uniformLocations[name], 1, GL_FALSE, glm::value_ptr(m));
}

void GLProgram::setUniformMat3(const std::string& name, const glm::mat3& m)
{
	if (!correctUniformName(name))
		return;

	glUniformMatrix4fv(m_uniformLocations[name], 1, GL_FALSE, glm::value_ptr(m));
}

void GLProgram::setUniformF(const std::string& name, f32 val)
{
	if (!correctUniformName(name))
		return;

	glUniform1f(m_uniformLocations[name], val);
}

void GLProgram::setUniformI(const std::string& name, i32 val)
{
	if (!correctUniformName(name))
		return;

	glUniform1i(m_uniformLocations[name], val);
}

void GLProgram::setUniformB(const std::string& name, bool val)
{
	if (!correctUniformName(name))
		return;

	glUniform1i(m_uniformLocations[name], val);
}

void GLProgram::recordUniformLocation(const std::string& name, u32 location)
{
	if (m_uniformLocations.count(name) != 0)
		return;

	std::cout << "Recorded " << name << " at position " << location << " \n";
	m_uniformLocations[name] = location;
}

void GLProgram::checkHandleValue()
{
	if (m_handle == 0)
	{
		m_handle = glCreateProgram();
		std::cout << "ProgramHandle: " << m_handle << "\n";
		if (m_handle == 0)
			std::cerr << "Error creating program object\n";
	}	
}

bool GLProgram::linkedCorrectly() const
{
	GLint status;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cerr << "Failed to link shader program!\n";
		
		GLint logLen;
		char infoLog[512];
		glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0) {
			GLsizei written;
			glGetProgramInfoLog(m_handle, logLen, &written, infoLog);
			std::cerr << "Program log: \n" << infoLog;
		}
		return false;
	}
	return true;
}

bool GLProgram::correctUniformName(const std::string& uniformName)
{
	return m_uniformLocations.find(uniformName) != m_uniformLocations.end();
}
