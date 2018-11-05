#include "PlayerInputComponent.h"

void PlayerInputComponent::Initialise(GameObject* _gameObject)
{
	m_gameObject = _gameObject;
}

void PlayerInputComponent::Update()
{
	if (InputHandler::GetKeyHold(SDL_SCANCODE_W))
	{
		m_gameObject->GetPhysicsComponent()->GetRigidBody()->applyCentralImpulse(btVector3(0.0f, 0.0f, -1.0f));
	}
	if (InputHandler::GetKeyHold(SDL_SCANCODE_S))
	{
		m_gameObject->GetPhysicsComponent()->GetRigidBody()->applyCentralImpulse(btVector3(0.0f, 0.0f, 1.0f));
	}
	if (InputHandler::GetKeyHold(SDL_SCANCODE_A))
	{
		m_gameObject->GetPhysicsComponent()->GetRigidBody()->applyCentralImpulse(btVector3(-1.0f, 0.0f, 0.0f));
	}
	if (InputHandler::GetKeyHold(SDL_SCANCODE_D))
	{
		m_gameObject->GetPhysicsComponent()->GetRigidBody()->applyCentralImpulse(btVector3(1.0f, 0.0f, 0.0f));
	}
	if (InputHandler::GetKeyPress(SDL_SCANCODE_SPACE))
	{
		m_gameObject->GetPhysicsComponent()->GetRigidBody()->applyCentralImpulse(btVector3(0.0f, 10.0f, 0.0f));
	}
}
