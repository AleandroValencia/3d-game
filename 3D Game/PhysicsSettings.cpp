#include "PhysicsSettings.h"

PhysicsSettings::PhysicsSettings()
{
	m_gravity = -9.81f;
	m_overlappingPairCache = new btDbvtBroadphase();
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_solver = new btSequentialImpulseConstraintSolver;
	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);
	m_dynamicsWorld->setGravity(btVector3(0, m_gravity, 0));
}

PhysicsSettings::~PhysicsSettings()
{
	for (int i = m_dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		m_dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	for (int i = 0; i < m_collisionShapes.size(); ++i)
	{
		btCollisionShape* shape = m_collisionShapes[i];
		m_collisionShapes[i] = 0;
		delete shape;
	}

	delete m_collisionConfiguration;
	m_collisionConfiguration = nullptr;
	delete m_dispatcher;
	m_dispatcher = nullptr;
	delete m_solver;
	m_solver = nullptr;
	delete m_overlappingPairCache;
	m_overlappingPairCache = nullptr;
	delete m_dynamicsWorld;
	m_dynamicsWorld = nullptr;
}

void PhysicsSettings::SetGravity(float _gravity)
{
	m_gravity = _gravity;
	m_dynamicsWorld->setGravity(btVector3(0, m_gravity, 0));
}

float PhysicsSettings::GetGravity()
{
	return m_gravity;
}

btDiscreteDynamicsWorld * PhysicsSettings::World()
{
	return m_dynamicsWorld;
}
