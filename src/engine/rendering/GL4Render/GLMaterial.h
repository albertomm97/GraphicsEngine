#pragma once
#include "../Material.h"
#include "../RenderProgram.h"

#include <variant>

class GLProgram;

class GLMaterial : public Material
{
public:
	explicit GLMaterial();
	~GLMaterial() override = default;
	void addShaders(const std::vector<std::string>& shadersPath) override;
	void prepare() override;

private:
	struct VertexAttribData
	{
		u32 glType;
		u32 varCount;
	};

private:	
	std::string getShaderExtension(const std::string& fileName) const;
	std::tuple<u32, std::variant<f32, f64, u32, i32, bool>, u32> getAttributeSizeAndType(u32 type) const;
	ShaderType getShaderTypeFromString(const std::string& path) const;
};

