#include "GameObject.h"

GameObject::GameObject(Camera* _camera, GraphicsComponent* _graphics, InputComponent* _input, PhysicsComponent* _physics)
	: m_camera(_camera)
	, m_graphics(_graphics)
	, m_input(_input)
	, m_physics(_physics)
	, m_speed(0.1f)
{
	m_transform = new Transform();
	m_transform->position.z = -5.0f;
}

GameObject::~GameObject()
{
	delete m_transform;
	m_transform = nullptr;

	delete m_graphics;
	m_graphics = nullptr;

	delete m_input;
	m_input = nullptr;

	delete m_physics;
	m_physics = nullptr;
}

void GameObject::Initialise()
{
	if (m_graphics)
	{
		m_graphics->Initialise(this);
	}
	if (m_input)
	{
		m_input->Initialise(this);
	}
	if (m_physics)
	{
		m_physics->Initialise(this);
	}
}

void GameObject::Initialise(GLuint _program)
{
	Initialise();
	if (m_graphics)
	{
		m_graphics->SetProgram(_program);
	}
}

void GameObject::SetTexture(std::string _filePath)
{
	m_graphics->SetTexture(_filePath);
}

void GameObject::SetTextures(std::vector<std::string>& _filePath)
{
	m_graphics->SetTextures(_filePath);
}

void GameObject::UpdateInput()
{
	if (m_input != nullptr)
	{
		m_input->Update();
	}
}

void GameObject::UpdatePhysics()
{
	if (m_physics != nullptr)
	{
		m_physics->Update();
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
		m_graphics->Update();
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