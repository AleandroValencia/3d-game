#ifndef _PLAYERINPUTCOMPONENT_H__
#define _PLAYERINPUTCOMPONENT_H__
#pragma once

#include "InputComponent.h"
#include "GameObject.h"

class PlayerInputComponent : public InputComponent
{
public:
	PlayerInputComponent() {};
	~PlayerInputComponent() {};
	void Initialise(GameObject* _gameObject);
	void Update();

private:
};

#endif // !_PLAYERINPUTCOMPONENT_H__

