#pragma once

#include "../../core/common/Types.h"
#include "../RenderProgram.h"

#include <unordered_map>
#include <map>
#include <initializer_list>
#include <vector>


class GLProgram : public RenderProgram
{
public:
	GLProgram() = default;
	~GLProgram() override;

	GLProgram(const GLProgram& other) = delete;
	GLProgram(GLProgram&& other) = delete;

	GLProgram& operator=(const GLProgram& other) = delete;
	GLProgram& operator=(GLProgram&& other) = delete;

	void addShader(const std::string& path, ShaderType type) override;
	void link() override;
	void use() const override;
	u32 getHandle() const override;

	void setUniformVec2(const std::string& name, const glm::vec2& v) override;
	void setUniformVec3(const std::string& name, const glm::vec3& v) override;
	void setUniformVec4(const std::string& name, const glm::vec4& v) override;
	void setUniformMat4(const std::string& name, const glm::mat4& m) override;
	void setUniformMat3(const std::string& name, const glm::mat3& m) override;
	void setUniformF(const std::string& name, f32 val) override;
	void setUniformI(const std::string& name, i32 val) override;
	void setUniformB(const std::string& name, bool val) override;
	void recordUniformLocation(const std::string& name, u32 location) override;

private:
	void checkHandleValue();
	bool linkedCorrectly() const;
	bool correctUniformName(const std::string& uniformName);

private:
	u32 m_handle{ 0 };
	std::unordered_map<ShaderType, u32> m_shaderHandles;
	std::map<const std::string, u32> m_uniformLocations;
	bool m_linked{ false };
};

