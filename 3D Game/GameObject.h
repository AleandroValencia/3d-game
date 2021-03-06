#ifndef _GAMEOBJECT_H__
#define _GAMEOBJECT_H__
#pragma once

#include <assert.h>

#include "glm\glm.hpp"

#include "Camera.h"
#include "Light.h"
#include "GraphicsComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "TransformComponent.h"

enum COMPONENT
{
	GRAPHICS = 0,
	PHYSICS,
	INPUT
};

class GameObject
{
public:
	GameObject(std::string _name, Camera* _camera, Light* _light, GraphicsComponent* _graphics, InputComponent* _input, PhysicsComponent* _physics);
	~GameObject();

	void Initialise();
	void Initialise(GLuint _program);
	void SetTexture(std::string _filePath);
	void SetTextures(std::vector<std::string>& _filePath);
	void UpdateInput();
	void UpdatePhysics();
	void Render();

	std::string GetName() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;

	Camera* m_camera;
	Light* GetLight() const { return m_light; }

	void SetPosition(glm::vec3 _position);
	void SetPositionFromPhysics(glm::vec3 _position);
	void SetRotation(glm::vec3 _eulerAngles);
	void SetScale(glm::vec3 _scale);

	GraphicsComponent* GetGraphicsComponent()  { return m_graphics; }
	InputComponent* GetInputComponent()  { return m_input; }
	PhysicsComponent* GetPhysicsComponent()  { return m_physics; }

	void MoveForward() { m_transform->position += m_transform->forward * m_speed; }
	void MoveBackward() { m_transform->position -= m_transform->forward * m_speed; }
	void MoveLeft() { m_transform->position -= m_transform->right * m_speed; }
	void MoveRight() { m_transform->position += m_transform->right * m_speed; }

	void AddVelocity(glm::vec3 _velocity) { m_velocity += _velocity; }
	glm::vec3 GetVelocity() const { return m_velocity; }

private:
	std::string m_name;
	Light* m_light;
	GraphicsComponent* m_graphics;
	InputComponent* m_input;
	PhysicsComponent* m_physics;
	Transform* m_transform;
	float m_speed;

	glm::vec3 m_velocity;
	bool m_moving;
};

#endif // !_GAMEOBJECT_H__