#pragma once

#include "../../engine/core/common/Types.h"

#include <string>
#include <glm/glm.hpp>

enum class ShaderType
{
	VERTEX = 0,
	FRAG,
	GEOMETRY,
	TESSEV,
	TESSCONTROL,
	COMPUTE
};

class RenderProgram
{
public:
	virtual ~RenderProgram() = default;

	virtual void addShader(const std::string& path, ShaderType type) = 0;
	virtual void link() = 0;
	virtual void use() const = 0;
	virtual u32 getHandle() const = 0;

	virtual void setUniformVec2(const std::string& name, const glm::vec2& v) = 0;
	virtual void setUniformVec3(const std::string& name, const glm::vec3& v) = 0;
	virtual void setUniformVec4(const std::string& name, const glm::vec4& v) = 0;
	virtual void setUniformMat4(const std::string& name, const glm::mat4& m) = 0;
	virtual void setUniformMat3(const std::string& name, const glm::mat3& m) = 0;
	virtual void setUniformF(const std::string& name, f32 val) = 0;
	virtual void setUniformI(const std::string& name, i32 val) = 0;
	virtual void setUniformB(const std::string& name, bool val) = 0;

	virtual void recordUniformLocation(const std::string&, u32 location) = 0;
};