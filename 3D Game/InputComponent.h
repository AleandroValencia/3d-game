#ifndef _INPUTCOMPONENT_H__
#define _INPUTCOMPONENT_H__
#pragma once

class InputComponent
{
public:
	virtual ~InputComponent() {};
	virtual void Update() = 0;
};

#endif // !_INPUTCOMPONENT_H__
