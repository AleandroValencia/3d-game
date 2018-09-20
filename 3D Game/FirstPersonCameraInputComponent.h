#ifndef _FIRSTPERSONCAMERAINPUTCOMPONENT_H__
#define _FIRSTPERSONCAMERAINPUTCOMPONENT_H__
#pragma once

#include "GameObject.h"
#include "InputHandler.h"
#include "InputComponent.h"

class FirstPersonCameraInputComponent : public InputComponent
{
public:
	FirstPersonCameraInputComponent() {}
	~FirstPersonCameraInputComponent() {}
	void Initialise(GameObject* _parentObject);
	void Update();

};

#endif // !_FIRSTPERSONCAMERAINPUTCOMPONENT_H__

