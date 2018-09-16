#include "GameObject.h"

GameObject::GameObject(Camera* _camera, GraphicsComponent* _graphics, InputComponent* _input, PhysicsComponent* _physics)
	: m_camera(_camera)
	, m_graphics(_graphics)
	, m_input(_input)
	, m_physics(_physics)
{
	m_transform = new Transform();
	m_transform->position.z = -5.0f;
}

GameObject::~GameObject()
{
	delete m_transform;
	m_transform = nullptr;
}

void GameObject::Initialise(GLuint _program)
{
	m_graphics->Initialise();
	m_graphics->SetProgram(_program);
}

void GameObject::SetTexture(std::string _filePath)
{
	m_graphics->SetTexture(_filePath);
}

void GameObject::UpdateInput()
{
	if (m_input != nullptr)
	{
		m_input->Update(*this);
	}
}

void GameObject::UpdatePhysics()
{
	if (m_physics != nullptr)
	{
		m_physics->Update(*this);
	}
}

void GameObject::Render()
{
#if _DEBUG
	assert(m_transform != nullptr);
	assert(m_camera != nullptr);
#endif
	if (m_graphics != nullptr)
	{
		m_graphics->Update(*this);
	}
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
