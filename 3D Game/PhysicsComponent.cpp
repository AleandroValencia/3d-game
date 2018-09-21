#include "PhysicsComponent.h"

btVector3 PhysicsComponent::GetPosition() const
{
	btTransform transform;
	m_motionState->getWorldTransform(transform);
	return transform.getOrigin();
}

btQuaternion PhysicsComponent::GetRotation() const
{
	btTransform transform;
	m_motionState->getWorldTransform(transform);
	return btQuaternion(transform.getRotation());
}

btVector3 PhysicsComponent::GetEulerAngle() const
{
	btTransform transform;
	btScalar x;
	btScalar y;
	btScalar z;
	m_motionState->getWorldTransform(transform);
	transform.getRotation().getEulerZYX(x,y,z);
	btVector3 euler = btVector3(x,y,z);
	return euler;
}

void PhysicsComponent::SetPosition(glm::vec3 _position)
{
	btTransform transform;
	m_motionState->getWorldTransform(transform);
	transform.setOrigin(Utils::glmToBullet(_position));
	m_motionState->setWorldTransform(transform);
	m_motionState->m_startWorldTrans = transform;
	m_rigidBody->setCenterOfMassTransform(transform);
}

void PhysicsComponent::SetRotation(glm::vec3 _rotation)
{
	btVector3 btRotation = Utils::glmToBullet(_rotation);
	btQuaternion quat = btQuaternion(btRotation.getX(), btRotation.getY(), btRotation.getZ());
	btTransform transform;
	m_motionState->getWorldTransform(transform);
	transform.setRotation(quat);
	m_motionState->setWorldTransform(transform);
	m_motionState->m_startWorldTrans = transform;
	m_rigidBody->setCenterOfMassTransform(transform);
}