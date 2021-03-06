#ifndef _PHYSICSSETTINGS_H__
#define _PHYSICSSETTINGS_H__
#pragma once

#include "Dependencies\Bullet\include\btBulletDynamicsCommon.h"

class PhysicsSettings
{
public:
	PhysicsSettings();
	~PhysicsSettings();

	void SetGravity(float _gravity);
	float GetGravity();

	btDiscreteDynamicsWorld* World();
	void AddCollisionShape(btCollisionShape* _collisionShape);

private:
	float m_gravity;
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btCollisionDispatcher* m_dispatcher;
	btBroadphaseInterface* m_overlappingPairCache;
	btSequentialImpulseConstraintSolver* m_solver;
	btDiscreteDynamicsWorld* m_dynamicsWorld;
	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;
};

#endif // !_PHYSICSSETTINGS_H__

