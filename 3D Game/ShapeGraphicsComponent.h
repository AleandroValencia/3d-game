#ifndef _SHAPEGRAPHICSCOMPONENT_H__
#define _SHAPEGRAPHICSCOMPONENT_H__
#pragma once

#include "GameObject.h"
#include "GraphicsComponent.h"

class ShapeGraphicsComponent : public GraphicsComponent
{
public:
	ShapeGraphicsComponent(ModelType _shape) { m_shape = _shape; }
	~ShapeGraphicsComponent() {}

	void Initialise(GameObject* _gameObject);
	void Update();
private:
	ModelType m_shape;
};

#endif // !_SHAPEGRAPHICSCOMPONENT_H__

