#include "Light.h"

Light::Light(glm::vec3 _pos)
	: m_color(glm::vec3(1.0f, 1.0f, 1.0f))
	, m_ambientStrength(0.1f)
	, m_specularStrength(0.5f)
{
	m_transform = new Transform();
	m_transform->position = _pos;
}

Light::~Light()
{
	delete m_transform;
	m_transform = nullptr;
}
