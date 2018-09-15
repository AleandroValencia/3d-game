#include "SceneManager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

bool SceneManager::Initialise()
{
	bool success = true;

	return success;
}

SceneManager & SceneManager::Instance()
{
	if (s_SceneManager == nullptr)
	{
		s_SceneManager = new SceneManager();
	}
	return (*s_SceneManager);
}

void SceneManager::DestroyInstance()
{
	delete s_SceneManager;
	s_SceneManager = nullptr;
}
