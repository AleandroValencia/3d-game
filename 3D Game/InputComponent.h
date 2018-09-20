#ifndef _INPUTCOMPONENT_H__
#define _INPUTCOMPONENT_H__
#pragma once

class GameObject;

class InputComponent
{
public:
	virtual ~InputComponent() {};
	virtual void Initialise(GameObject* _parentObject) = 0;
	virtual void Update() = 0;

protected:
	GameObject* m_gameObject;
};

#endif // !_INPUTCOMPONENT_H__
