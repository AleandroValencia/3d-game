#include "PlayerInputComponent.h"

void PlayerInputComponent::Initialise(GameObject* _gameObject)
{
	m_gameObject = _gameObject;
}

void PlayerInputComponent::Update()
{
	float moveSpeed = 1.0f;
	glm::vec3 forwardDirection = glm::normalize(m_gameObject->m_camera->m_transform->forward) * moveSpeed;
	forwardDirection.y = 0.0f;
	glm::vec3 rightDirection = glm::normalize(m_gameObject->m_camera->m_transform->right) * moveSpeed;
	rightDirection.y = 0.0f;

	if (InputHandler::GetKeyHold(SDL_SCANCODE_W))
	{
		m_gameObject->GetPhysicsComponent()->GetRigidBody()->applyCentralImpulse(Utils::glmToBullet(forwardDirection));
	}
	if (InputHandler::GetKeyHold(SDL_SCANCODE_S))
	{
		m_gameObject->GetPhysicsComponent()->GetRigidBody()->applyCentralImpulse(Utils::glmToBullet(-forwardDirection));
	}
	if (InputHandler::GetKeyHold(SDL_SCANCODE_A))
	{
		m_gameObject->GetPhysicsComponent()->GetRigidBody()->applyCentralImpulse(Utils::glmToBullet(rightDirection));
	}
	if (InputHandler::GetKeyHold(SDL_SCANCODE_D))
	{
		m_gameObject->GetPhysicsComponent()->GetRigidBody()->applyCentralImpulse(Utils::glmToBullet(-rightDirection));
	}
	if (InputHandler::GetKeyPress(SDL_SCANCODE_SPACE))
	{
		m_gameObject->GetPhysicsComponent()->GetRigidBody()->applyCentralImpulse(btVector3(0.0f, 10.0f, 0.0f));
	}
}
