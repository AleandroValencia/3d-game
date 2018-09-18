#ifndef _GAME_H__
#define _GAME_H__
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <algorithm>
#include <vld.h>

#include "Dependencies\glew\glew.h"
#include "Dependencies\sdl\include\SDL_opengl.h"
#include "Dependencies\Bullet\include\btBulletDynamicsCommon.h"
#include "Dependencies\Dear_ImGui\imgui.h"
#include "Dependencies\Dear_ImGui\imgui_impl_sdl_gl3.h"

#include "PhysicsSettings.h"
#include "SceneManager.h"
#include "Utils.h"

#include "Camera.h"
#include "GameObject.h"
#include "ShapeGraphicsComponent.h"
#include "ShaderLoader.h"

class Game
{
public:
	~Game();
	static Game& Instance();

	void Initialise();
	void MainLoop();
	void ShutDown();

	PhysicsSettings* physics() { return m_physics; }
	SceneManager* scenemanager() { return m_sceneManager; }

private:
	void InitGameObjects();
	void HandleEvents(SDL_Event& _e);

	Game();
	static Game* m_instance;

	const char* m_Title = "3D Game";
	bool m_vSync = true;
	bool m_closeApplication = false;
	SDL_Window* m_Window = nullptr;
	SDL_GLContext m_Context;
	SDL_Event e;
	Uint64 m_currentTime = SDL_GetPerformanceCounter();

	PhysicsSettings* m_physics;
	SceneManager* m_sceneManager;

	GameObject* bob;
	Camera* camera;
	std::vector<GameObject*> m_gameObjects;
	std::vector<GraphicsComponent*> m_graphicsComponents;

	bool m_showWindow = true; 
};

#endif // !_GAME_H__