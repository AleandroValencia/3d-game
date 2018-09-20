#include "StaticPhysicsComponent.h"

StaticPhysicsComponent::StaticPhysicsComponent(btScalar _mass)
{
	m_mass = _mass; 
}

StaticPhysicsComponent::~StaticPhysicsComponent()
{
}

void StaticPhysicsComponent::Initialise(GameObject * _gameObject)
{
	m_collisionShape = new btBoxShape(Utils::glmToBullet(_gameObject->GetScale() / 2.0f));
	m_transform.setIdentity();
	m_transform.setOrigin(Utils::glmToBullet(_gameObject->GetPosition()));
	m_isDynamic = (m_mass != 0.0f);

	btVector3 localInertia(0, 0, 0);
	if (m_isDynamic)
		m_collisionShape->calculateLocalInertia(m_mass, localInertia);

	m_motionState = new btDefaultMotionState(m_transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(m_mass, m_motionState, m_collisionShape, localInertia);
	m_rigidBody = new btRigidBody(rbInfo);
}

void StaticPhysicsComponent::Update()
{

}
