#pragma once
#include "Entity.h"
#include "../rendering/Render.h"

enum class LightType
{
	DIRECTIONAL = 0,
	POINT = 1
};

class Light : public Entity
{
public:
	Light() = default;

	Light(glm::vec3 position, glm::vec4 color, LightType type)
	{
		setPosition(position);
		m_color = color;
		m_type = type;
		/*m_ambient = ambient;
		m_ambientStrengh = ambientStrengh;
		m_specularStrengh = specularStrengh;
		m_constAttenuation = kAttenuation;
		m_linearAttenuation = lAttenuation;
		m_quadraticAttenuation = qAttenuation;
		m_direction = direction;*/
		m_enabled = true;
	}

	Light(glm::vec3 position, glm::vec4 color, glm::vec3 ambient, f32 ambientStrengh, f32 specularStrengh, f32 kAttenuation, f32 lAttenuation, f32 qAttenuation, glm::vec3 direction, LightType type)
	{
		setPosition(position);
		m_color = color;
		m_type = type;
		m_ambient = ambient;
		m_ambientStrengh = ambientStrengh;
		m_specularStrengh = specularStrengh;
		m_constAttenuation = kAttenuation;
		m_linearAttenuation = lAttenuation;
		m_quadraticAttenuation = qAttenuation;
		m_direction = direction;
		m_enabled = true;
	}

	~Light() override = default;
	
	inline void setLightType(LightType type) { m_type = type; }
	inline LightType getLightType() const { return m_type; }
	
	inline const glm::vec4& getColor() const { return m_color; }
	inline void setColor(const glm::vec4& color) { m_color = color; }
	
	inline void enableLight(bool condition) { m_enabled = condition; }

	inline void setAmbient(const glm::vec3& ambient) { m_ambient = ambient; }
	inline const glm::vec3& getAmbient() { return m_ambient; }

	inline void setAmbientStrengh(f32 ambient) { m_ambientStrengh = ambient; }
	inline f32 getAmbientStrengh() { return m_ambientStrengh; }

	inline void setSpecularStrengh(f32 specular) { m_specularStrengh = specular; }
	inline f32 getSpecularStrengh() { return m_specularStrengh; }

	inline float getLinearAttenuation() const { return m_linearAttenuation; }
	inline void  setLinearAttenuation(f32 att) { m_linearAttenuation = att; }

	inline float getConstAttenuation() const { return m_constAttenuation; }
	inline void  setConstAttenuation(f32 att) { m_constAttenuation = att; }

	inline float getQuadraticAttenuation() const { return m_quadraticAttenuation; }
	inline void  setQuadraticAttenuation(f32 att) { m_quadraticAttenuation = att; }

	inline const glm::vec3& getDirection() { return m_direction; }
	inline const void setDirection(const glm::vec3& direction) { m_direction = direction; }
	
	inline void updatePerFrameData(PerframePhongLightData& data) {
		data.position = m_position;
		data.color = m_color;
		data.ambient = m_ambient;
		data.ambientStrengh = m_ambientStrengh;
		data.specularStrengh = m_specularStrengh;
		data.kAttenuation = m_constAttenuation;
		data.lAttenuation = m_linearAttenuation;
		data.qAttenuation = m_quadraticAttenuation;
		data.enabled = m_enabled;
		data.type = static_cast<i32>(m_type);
		data.direction = m_direction;
	}

	virtual void update() override { };

private:
	LightType m_type;
	bool m_enabled;

	glm::vec4 m_color;

	glm::vec3 m_ambient;
	f32 m_ambientStrengh;
	
	f32 m_specularStrengh;

	f32 m_constAttenuation;
	f32 m_linearAttenuation;
	f32 m_quadraticAttenuation;

	glm::vec3 m_direction;
};
