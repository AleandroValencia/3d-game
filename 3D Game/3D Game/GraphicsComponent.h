#ifndef _GRAPHICSCOMPONENT_H__
#define _GRAPHICSCOMPONENT_H__
#pragma once

class GraphicsComponent
{
public:
	virtual ~GraphicsComponent() {};
	virtual void Update() = 0;
};
#endif // !_GRAPHICSCOMPONENT_H__