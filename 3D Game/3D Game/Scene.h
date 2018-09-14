#ifndef _SCENE_H__
#define _SCENE_H__
#pragma once

class Scene
{
public:
	Scene();
	~Scene();

	void Initialise();
	void Update(float _deltaTime);
	void Render();

private:

};

#endif // !_SCENE_H__

