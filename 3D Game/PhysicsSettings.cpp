#include "PhysicsSettings.h"

PhysicsSettings* PhysicsSettings::s_PhysicsSettings = nullptr;
float PhysicsSettings::m_gravity = -9.81f;
btDefaultCollisionConfiguration* PhysicsSettings::m_collisionConfiguration = nullptr;
btCollisionDispatcher* PhysicsSettings::m_dispatcher;
btBroadphaseInterface* PhysicsSettings::m_overlappingPairCache;
btSequentialImpulseConstraintSolver* PhysicsSettings::m_solver;
btDiscreteDynamicsWorld* PhysicsSettings::m_dynamicsWorld;

PhysicsSettings::PhysicsSettings()
{
	m_gravity = -9.81;
	m_overlappingPairCache = new btDbvtBroadphase();
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_solver = new btSequentialImpulseConstraintSolver;
	m_dynamicsWorld = new btDiscreteDynamicsWorld(m_dispatcher, m_overlappingPairCache, m_solver, m_collisionConfiguration);
	m_dynamicsWorld->setGravity(btVector3(0, m_gravity, 0));
}

PhysicsSettings::~PhysicsSettings()
{
}

PhysicsSettings& PhysicsSettings::Instance()
{
	if (s_PhysicsSettings == nullptr)
	{
		s_PhysicsSettings = new PhysicsSettings();
	}
	return *s_PhysicsSettings;
}

void PhysicsSettings::DestroyInstance()
{
	// Cleanup physics
	//remove the rigidbodies from the dynamics world and delete them
	if (m_dynamicsWorld != nullptr)
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

	delete s_PhysicsSettings;
	s_PhysicsSettings = nullptr;
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
