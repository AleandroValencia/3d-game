#ifndef _THIRDPERSONCAMERAINPUTCOMPONENT_H__
#define _THIRDPERSONCAMERAINPUTCOMPONENT_H__
#pragma once

#include "GameObject.h"
#include "InputHandler.h"
#include "InputComponent.h"

class ThirdPersonCameraInputComponent : public InputComponent
{
public:
	ThirdPersonCameraInputComponent(GameObject* _followTarget) : m_followTarget(_followTarget) {}
	~ThirdPersonCameraInputComponent() {}
	void Initialise(GameObject* _parentObject);
	void Update();

private:
	GameObject* m_followTarget;
};

#endif // !_THIRDPERSONCAMERAINPUTCOMPONENT_H__