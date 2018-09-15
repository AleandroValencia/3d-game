#ifndef _LIGHT_H__
#define _LIGHT_H__
#pragma once

#include "glm\glm.hpp"

class Transform;

class Light
{
public:
	Light();
	~Light();

private:
	Transform* m_transform;
	glm::vec3 m_color;
};

#endif // !_LIGHT_H__

