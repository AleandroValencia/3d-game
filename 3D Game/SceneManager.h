#ifndef _SCENEMANAGER_H__
#define _SCENEMANAGER_H__
#pragma once

class SceneManager
{
public:
	~SceneManager();

	static bool Initialise();

	static SceneManager& Instance();
	static void DestroyInstance();
protected:
	static SceneManager* s_SceneManager;

private:
	SceneManager();

};

#endif // !_SCENEMANAGER_H__


