#ifndef _STATICPHYSICSCOMPONENT_H__
#define _STATICPHYSICSCOMPONENT_H__
#pragma once

#include "GameObject.h"
#include "PhysicsComponent.h"

class StaticPhysicsComponent : public PhysicsComponent
{
public:
	StaticPhysicsComponent(btScalar _mass);
	~StaticPhysicsComponent();

	void Initialise(GameObject* _gameObject);
	void Update();

private:
};

#endif // !_STATICPHYSICSCOMPONENT_H__

