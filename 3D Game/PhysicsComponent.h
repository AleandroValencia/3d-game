#ifndef _PHYSICSCOMPONENT_H__
#define _PHYSICSCOMPONENT_H__
#pragma once

#include "Dependencies\Bullet\include\btBulletDynamicsCommon.h"

class GameObject;

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {};
	virtual void Update(GameObject& _gameObject) = 0;

private:
	btCollisionShape* m_collisionShape;
	btTransform m_transform;
	btScalar m_mass;
	bool m_isDynamic;
	btDefaultMotionState* m_motionState;
	btRigidBody* m_rigidBody;
};

#endif // !_PHYSICSCOMPONENT_H__

