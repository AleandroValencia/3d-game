#ifndef _GAME_H__
#define _GAME_H__
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <algorithm>
#include <map>
#if _DEBUG
#include <vld.h>
#endif

#include "Dependencies\glew\glew.h"
#include "Dependencies\sdl\include\SDL_opengl.h"
#include "Dependencies\Bullet\include\btBulletDynamicsCommon.h"

#include "PlayerInputComponent.h"
#include "FirstPersonCameraInputComponent.h"
#include "ThirdPersonCameraInputComponent.h"

#include "InputHandler.h"
#include "PhysicsSettings.h"
#include "SceneManager.h"
#include "Utils.h"

#include "Camera.h"
#include "Light.h"
#include "GameObject.h"
#include "ShapeGraphicsComponent.h"
#include "ShaderLoader.h"
#include "StaticPhysicsComponent.h"

#include "PhysicsDebugRenderer.h"

enum GAMEOBJECTNAME
{
	SKYBOX = 0,
	BOX,
	CAMERA_CONTROLLER,
	LIGHT_BOX, 
	GROUND
};

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
	InputHandler* m_input;

	GameObject* bob;
	Camera* camera;
	Light* light;
	std::map<GAMEOBJECTNAME, GameObject*> m_gameObjects;
	std::vector<GraphicsComponent*> m_graphicsComponents;
	std::vector<InputComponent*> m_inputComponents;
	std::vector<PhysicsComponent*> m_physicsComponents;

	bool m_showWindow = true; 

	PhysicsDebugRenderer* m_physicsRenderer;
};

#endif // !_GAME_H__