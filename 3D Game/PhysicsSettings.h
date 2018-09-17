#ifndef _PHYSICSSETTINGS_H__
#define _PHYSICSSETTINGS_H__
#pragma once

#include "Dependencies\Bullet\include\btBulletDynamicsCommon.h"

class PhysicsSettings
{
public:
	~PhysicsSettings();

	static PhysicsSettings& Instance();
	static void DestroyInstance();

	static void SetGravity(float _gravity);
	static float GetGravity();

	static btDiscreteDynamicsWorld* World();
private:
	PhysicsSettings();
	static PhysicsSettings* s_PhysicsSettings;

	static float m_gravity;
	static btDefaultCollisionConfiguration* m_collisionConfiguration;
	static btCollisionDispatcher* m_dispatcher;
	static btBroadphaseInterface* m_overlappingPairCache;
	static btSequentialImpulseConstraintSolver* m_solver;
	static btDiscreteDynamicsWorld* m_dynamicsWorld;
};

#endif // !_PHYSICSSETTINGS_H__

