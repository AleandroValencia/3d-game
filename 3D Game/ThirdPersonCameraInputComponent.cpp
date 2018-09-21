#include "ThirdPersonCameraInputComponent.h"

void ThirdPersonCameraInputComponent::Initialise(GameObject * _parentObject)
{
	m_gameObject = _parentObject;
}

void ThirdPersonCameraInputComponent::Update()
{
	if (SDL_GetRelativeMouseMode())
		m_gameObject->m_camera->RotateAround(m_followTarget->GetPosition() ,glm::vec3(-InputHandler::GetYOffset(), InputHandler::GetXOffset(), 0.0f));
}
