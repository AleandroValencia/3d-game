#ifndef _PHYSICSCOMPONENT_H__
#define _PHYSICSCOMPONENT_H__
#pragma once

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {};
	virtual void Update() = 0;
};

#endif // !_PHYSICSCOMPONENT_H__

