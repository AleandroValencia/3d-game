#ifndef _GAMEOBJECT_H__
#define _GAMEOBJECT_H__
#pragma once

#include "glm\glm.hpp"

#include "Camera.h"
#include "TransformComponent.h"

class GraphicsComponent;
class InputComponent;
class PhysicsComponent;

class GameObject
{
public:
	GameObject(GraphicsComponent* _graphics, InputComponent* _input, PhysicsComponent* _physics);
	~GameObject();

	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;

	Camera* m_camera;
	Transform* m_transform;
private:
	GraphicsComponent* m_graphics;
	InputComponent* m_input;
	PhysicsComponent* m_physics;
};

#endif // !_GAMEOBJECT_H__