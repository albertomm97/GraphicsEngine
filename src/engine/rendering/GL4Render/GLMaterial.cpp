#include "GLMaterial.h"
#include "GLProgram.h"
#include "../Vertex.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <array>
#include <map>
#include <iostream>
#include <typeinfo>

std::map<std::string, ShaderType> extensions = {
		{".vs",   ShaderType::VERTEX},
		{".vert", ShaderType::VERTEX},
		{"_vert.glsl", ShaderType::VERTEX},
		{".vert.glsl", ShaderType::VERTEX },
		{".gs",   ShaderType::GEOMETRY},
		{".geom", ShaderType::GEOMETRY},
		{ ".geom.glsl", ShaderType::GEOMETRY },
		{".tcs",  ShaderType::TESSCONTROL},
		{ ".tcs.glsl",  ShaderType::TESSCONTROL },
		{ ".tes",  ShaderType::TESSEV },
		{".tes.glsl",  ShaderType::TESSEV},
		{".fs",   ShaderType::FRAG},
		{".frag", ShaderType::FRAG},
		{"_frag.glsl", ShaderType::FRAG},
		{".frag.glsl", ShaderType::FRAG},
		{".cs",   ShaderType::COMPUTE},
		{ ".cs.glsl",   ShaderType::COMPUTE }
};

GLMaterial::GLMaterial()
{
	std::cout << "MaterialCreatedSuccesfully\n";
	setRenderProgram(std::make_shared<GLProgram>());
}

void GLMaterial::addShaders(const std::vector<std::string>& shadersPath)
{
	auto renderProgram = getRenderProgram();
	for (const auto& shaderPath : shadersPath)
	{
		auto type = getShaderTypeFromString(shaderPath);
		renderProgram->addShader(shaderPath, type);
	}

	renderProgram->link();
}

void GLMaterial::prepare()
{
	auto renderProgram = getRenderProgram();
	auto programHandle = renderProgram->getHandle();
	
	// Query vertex attributes (name_lengh, type, location)
	GLint numAttribs;
	glGetProgramInterfaceiv(programHandle, GL_PROGRAM_INPUT,
		GL_ACTIVE_RESOURCES, &numAttribs);
	GLenum properties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION };
	
	std::map<u32, VertexAttribData> location_attribute;
	std::size_t vertexDataSize{ 0 };
	std::vector<size_t> offsets;
	for (int i = 0; i < numAttribs; ++i) 
	{
		// Get the properties of attribute
		GLint results[3];
		glGetProgramResourceiv(programHandle, GL_PROGRAM_INPUT,
			i, 3, properties, 3, NULL, results);

		// From the GL_TYPE (GL_VEC_4), get the variable count, the system type and the atomic gltype (GL_FLOAT)
		auto [count, systype, gltype] = getAttributeSizeAndType(results[1]);
		auto varCount = count;
		auto type = gltype;

		// Visit the std::variant so we can access the systype and calculate the offsets and vertexDataSize
		std::visit([&offsets, &vertexDataSize, varCount](auto&& e) {
			offsets.push_back(vertexDataSize);
			vertexDataSize += varCount * sizeof(e);
		}, systype);
		
		std::cout << "VertexDataSize " << i << ": " << vertexDataSize << "\n";
		std::cout << "Location " << i << ": " << results[2] << "\n";
		// Set the variables
		VertexAttribData attribData;
		attribData.glType = type;
		attribData.varCount = varCount;

		location_attribute[results[2]] = attribData;
	}

	std::cout << "Attributes number: " << numAttribs << "\n";
	std::cout << "Attributes size: " << vertexDataSize << "\n";
	
	// Loop through each attribute and set up OpenGL data.
	auto i = 0;
	for (auto& values : location_attribute)
	{
		auto vertexAttribute = values.first;
		auto attribData = values.second;

		glVertexAttribPointer(vertexAttribute, attribData.varCount, attribData.glType, GL_FALSE, vertexDataSize, (void*)offsets[i]);
		glEnableVertexAttribArray(vertexAttribute);
		
		i += 1;
	}

	// Query uniforms 
	GLint numUniforms;
	glGetProgramInterfaceiv(programHandle, GL_UNIFORM,
		GL_ACTIVE_RESOURCES, &numUniforms);
	std::cout << "Num uniforms (including the uniforms within blocks): " << numUniforms << "\n";
	GLenum uniformProperties[] = { GL_NAME_LENGTH, GL_TYPE, GL_LOCATION, GL_BLOCK_INDEX };
	
	for (int i = 0; i < numUniforms; ++i) 
	{
		GLint results[4];
		glGetProgramResourceiv(programHandle, GL_UNIFORM,
			i, 4, uniformProperties, 4, NULL, results);

		// We only want the uniforms that are outside uniform blocks (when its block index is -1)
		if (results[3] == -1)
		{
			GLint nameBufSize = results[0] + 1;
			std::vector<char> name(nameBufSize);
			glGetProgramResourceName(programHandle, GL_UNIFORM, i,
				nameBufSize, NULL, name.data());

			std::string uniformName{ name.data() };
			std::cout << "Name: " << uniformName << "\n";
			std::cout << "Location: " << results[2] << "\n";

			// Cache uniform location
			renderProgram->recordUniformLocation(uniformName, results[2]);
		}
	}

	// Query uniforms blocks (only for information)
	GLint uniformBlockNum;
	glGetProgramInterfaceiv(programHandle, GL_UNIFORM_BLOCK,
		GL_ACTIVE_RESOURCES, &uniformBlockNum);
	std::cout << "Num uniform blocks: " << uniformBlockNum << "\n";
	
	std::array<GLenum, 3> blockProperties{ GL_NAME_LENGTH, GL_NUM_ACTIVE_VARIABLES, GL_BUFFER_DATA_SIZE };
	std::array<GLint, 3> blockData{};

	u32 uboHandle;
	for (int i = 0; i < uniformBlockNum; ++i)
	{
		glGetProgramResourceiv(programHandle, GL_UNIFORM_BLOCK,
			i, blockProperties.size(), blockProperties.data(), blockData.size(), NULL, blockData.data());
	
		GLint nameBufSize = blockData[0] + 1;
		std::vector<char> blockName(nameBufSize);
		glGetProgramResourceName(programHandle, GL_UNIFORM_BLOCK, i,
			nameBufSize, NULL, blockName.data());
		
		auto uniformBlockIndex = glGetUniformBlockIndex(programHandle, blockName.data());
		std::cout << "Uniform block name: " << std::string(blockName.data()) << "\n";
		std::cout << "Uniform index: " << uniformBlockIndex << "\n";
		std::cout << "active variables: " << blockData[1] << "\n";

		// We dont need to bind since we specified that information within the shader
		// What's better? Specify the binding point within the shader or binding here in runtime?
		//glUniformBlockBinding(programHandle, uniformBlockIndex, 0);
	}
}

ShaderType GLMaterial::getShaderTypeFromString(const std::string& path) const
{
	auto ext = getShaderExtension(path);
	std::cout << "Extension: " << ext << "\n";
	return extensions[ext];
}

std::tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32> GLMaterial::getAttributeSizeAndType(u32 type) const
{
	switch (type)
	{
	case GL_FLOAT:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(1, 0.0f, GL_FLOAT);
	case GL_FLOAT_VEC2:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(2, 0.0f, GL_FLOAT);
	case GL_FLOAT_VEC3:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(3, 0.0f, GL_FLOAT);
	case GL_FLOAT_VEC4:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(4, 0.0f, GL_FLOAT);
	case GL_DOUBLE:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(1, static_cast<double>(0.0f), GL_DOUBLE);
	case GL_INT:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(1, 0, GL_INT);
	case GL_UNSIGNED_INT:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(1, static_cast<unsigned int>(0), GL_UNSIGNED_INT);
	case GL_BOOL:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(1, true, GL_BOOL);
	case GL_FLOAT_MAT2:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(4, 0.0f, GL_FLOAT);
	case GL_FLOAT_MAT3:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(9, 0.0f, GL_FLOAT);
	case GL_FLOAT_MAT4:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(16, 0.0f, GL_FLOAT);
	default:
		return std::make_tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32>(0, 0, GL_NONE);
	}
}


std::string GLMaterial::getShaderExtension(const std::string& fileName) const
{
	size_t dotLoc = fileName.find_last_of('.');
	if (dotLoc != std::string::npos) {
		std::string ext = fileName.substr(dotLoc);
		if (ext == ".glsl") {

			size_t loc = fileName.find_last_of('.', dotLoc - 1);
			if (loc == std::string::npos) {
				loc = fileName.find_last_of('_', dotLoc - 1);
			}
			if (loc != std::string::npos) {
				return fileName.substr(loc);
			}
		}
		else {
			return ext;
		}
	}
	return "";
}
