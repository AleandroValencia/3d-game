#ifndef _LIGHT_H__
#define _LIGHT_H__
#pragma once

#include "glm\glm.hpp"

#include "TransformComponent.h"

class Light
{
public:
	Light(glm::vec3 _pos);
	~Light();

	glm::vec3 GetPosition() const { return m_transform->position; }
	glm::vec3 GetColor() const { return m_color; }
	float GetAmbient() const { return m_ambientStrength; }
	float GetSpecular() const { return m_specularStrength; }

private:
	Transform* m_transform;
	glm::vec3 m_color;
	float m_ambientStrength;
	float m_specularStrength;
};

#endif // !_LIGHT_H__

