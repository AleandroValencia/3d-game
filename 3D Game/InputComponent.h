#ifndef _INPUTCOMPONENT_H__
#define _INPUTCOMPONENT_H__
#pragma once

class GameObject;

class InputComponent
{
public:
	virtual ~InputComponent() {};
	virtual void Update(GameObject& _gameObject) = 0;
};

#endif // !_INPUTCOMPONENT_H__
