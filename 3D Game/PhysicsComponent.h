#ifndef _PHYSICSCOMPONENT_H__
#define _PHYSICSCOMPONENT_H__
#pragma once

class GameObject;

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {};
	virtual void Update(GameObject& _gameObject) = 0;
};

#endif // !_PHYSICSCOMPONENT_H__

