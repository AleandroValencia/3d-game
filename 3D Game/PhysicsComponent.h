#ifndef _PHYSICSCOMPONENT_H__
#define _PHYSICSCOMPONENT_H__
#pragma once

#include "Dependencies\Bullet\include\btBulletDynamicsCommon.h"
#include "Utils.h"

class GameObject;

class PhysicsComponent
{
public:
	virtual ~PhysicsComponent() {};
	virtual void Initialise(GameObject* _gameObject) = 0;
	virtual void Update() = 0;

	btVector3 GetPosition() const;
	btQuaternion GetRotation() const;
	btVector3 GetEulerAngle() const;	// NOTE the yaw,pitch,roll

	void SetPosition(glm::vec3 _position);
	void SetRotation(glm::vec3 _rotation);

	void SetScale(glm::vec3 _scale) { m_collisionShape->setLocalScaling(Utils::glmToBullet(_scale)); }
	btCollisionShape* GetCollisionShape() const { return m_collisionShape; }
	btRigidBody* GetRigidBody() const { return m_rigidBody; }

protected:
	GameObject* m_gameObject;
	btCollisionShape* m_collisionShape;
	btScalar m_mass;
	bool m_isDynamic;
	btDefaultMotionState* m_motionState;
	btRigidBody* m_rigidBody;
};

#endif // !_PHYSICSCOMPONENT_H__

