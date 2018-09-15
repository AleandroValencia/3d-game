#ifndef _SHAPEGRAPHICSCOMPONENT_H__
#define _SHAPEGRAPHICSCOMPONENT_H__
#pragma once

#include "GameObject.h"
#include "GraphicsComponent.h"

class ShapeGraphicsComponent : public GraphicsComponent
{
public:
	ShapeGraphicsComponent() {}
	~ShapeGraphicsComponent() {}

	void Initialise();
	void Update(GameObject& _gameObject);
private:
	ModelType m_shape;
};

#endif // !_SHAPEGRAPHICSCOMPONENT_H__
