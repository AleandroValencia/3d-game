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
	m_gameObject = _gameObject;
	m_collisionShape = new btBoxShape(Utils::glmToBullet(m_gameObject->GetScale()));
	btTransform objectTransform;
	objectTransform.setIdentity();
	objectTransform.setOrigin(Utils::glmToBullet(m_gameObject->GetPosition()));
	m_isDynamic = (m_mass != 0.0f);

	btVector3 localInertia(0, 0, 0);
	if (m_isDynamic)
		m_collisionShape->calculateLocalInertia(m_mass, localInertia);

	m_motionState = new btDefaultMotionState(objectTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(m_mass, m_motionState, m_collisionShape, localInertia);
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setActivationState(DISABLE_DEACTIVATION);
}

void StaticPhysicsComponent::Update()
{
	m_gameObject->SetPositionFromPhysics(Utils::bulletToGLM(GetPosition()));
	m_gameObject->SetRotation(Utils::bulletToGLM(GetEulerAngle()));
	if (m_gameObject->GetVelocity() != glm::vec3(0.0f))
	{
		m_rigidBody->setLinearVelocity(Utils::glmToBullet(m_gameObject->GetVelocity()));
	}
}
