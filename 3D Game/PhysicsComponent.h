#ifndef _PHYSICSCOMPONENT_H__
#define _PHYSICSCOMPONENT_H__
#pragma once

#include "Dependencies\Bullet\include\btBulletDynamicsCommon.h"

class GameObject;

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {};
	virtual void Initialise(GameObject* _gameObject) = 0;
	virtual void Update() = 0;

protected:
	GameObject* m_gameObject;

	btCollisionShape* m_collisionShape;
	btTransform m_transform;
	btScalar m_mass;
	bool m_isDynamic;
	btDefaultMotionState* m_motionState;
	btRigidBody* m_rigidBody;
};

#endif // !_PHYSICSCOMPONENT_H__

