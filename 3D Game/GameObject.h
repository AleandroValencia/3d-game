#ifndef _GAMEOBJECT_H__
#define _GAMEOBJECT_H__
#pragma once

#include <assert.h>

#include "glm\glm.hpp"

#include "Camera.h"
#include "GraphicsComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"

class GameObject
{
public:
	GameObject(Camera* _camera, GraphicsComponent* _graphics, InputComponent* _input, PhysicsComponent* _physics);
	~GameObject();

	void Initialise(GLuint _program);
	void SetTexture(std::string _filePath);
	void UpdateInput();
	void UpdatePhysics();
	void Render();

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