#include "GameObject.h"

GameObject::GameObject(GraphicsComponent* _graphics, InputComponent* _input, PhysicsComponent* _physics)
	: m_graphics(_graphics)
	, m_input(_input)
	, m_physics(_physics)
{
}

GameObject::~GameObject()
{
}

glm::vec3 GameObject::GetPosition() const
{
	return m_transform->position;
}

glm::vec3 GameObject::GetRotation() const
{
	return m_transform->rotation;
}

glm::vec3 GameObject::GetScale() const
{
	return m_transform->scale;
}
