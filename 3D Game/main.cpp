//Using SDL and standard IO
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

#include "SceneManager.h"
#include "Utils.h"

#include "PhysicsSettings.h"

#include "Camera.h"
#include "GameObject.h"
#include "ShapeGraphicsComponent.h"
#include "ShaderLoader.h"

// --Global Variables--
const char* gTitle = "3D Game";
SDL_Window* gWindow = nullptr;
SDL_GLContext gContext;
bool vSync = true;

Uint64 currentTime = SDL_GetPerformanceCounter();
Uint64 elapsedTime = 0;
double deltaTime = 0;

GameObject* bob;
Camera* camera;

std::vector<GraphicsComponent*> m_graphicsComponents;

void InitSDL()
{
	SDL_Init(SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow(gTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Utils::WIDTH, Utils::HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	gContext = SDL_GL_CreateContext(gWindow);
	glewInit();
	if (vSync)
	{
		SDL_GL_SetSwapInterval(1);
	}
}

void CloseSDL()
{
	SDL_GL_DeleteContext(gContext);
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;
	SDL_Quit();
}

void InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplSdlGL3_Init(gWindow);
	ImGui::StyleColorsDark();
}

void HandleEvents(SDL_Event& _e, bool& _quit)
{
	while (SDL_PollEvent(&_e) != 0)
	{
		ImGui_ImplSdlGL3_ProcessEvent(&_e);
		if (_e.type == SDL_QUIT)
		{
			_quit = true;
		}
		else if (_e.type == SDL_KEYDOWN)
		{
			switch (_e.key.keysym.sym)
			{
			case SDLK_UP:
				printf("Pressed up\n");
				break;
			case SDLK_DOWN:
				break;
			case SDLK_LEFT:
				break;
			case SDLK_RIGHT:
				break;
			default:
				break;
			}
		}
	}
}

void Init()
{
	camera = new Camera();

	ShaderLoader sl;
	GLuint program = sl.CreateProgram("Assets/Shaders/Vertex/Texture.vs", "Assets/Shaders/Fragment/Texture.fs");

	bob = new GameObject(camera, new ShapeGraphicsComponent(), nullptr, nullptr);
	bob->Initialise(program);
	bob->SetTexture("Assets/Textures/Grass.jpg");
	m_graphicsComponents.push_back(bob->GetGraphicsComponent());
}

int main(int argc, char* args[])
{
	srand(static_cast<unsigned int>(time(NULL)));
	bool closeApplication = false;
	SDL_Event e;

	bool showWindow = true;

	InitSDL();
	InitImGui();
	Init();

	// Game loop
	while (!closeApplication)
	{
		// Calculate Delta Time
		elapsedTime = currentTime;
		currentTime = SDL_GetPerformanceCounter();
		deltaTime = static_cast<double>((currentTime - elapsedTime) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency()));
		deltaTime = deltaTime * 0.001f;	// Convert ms to s

		HandleEvents(e, closeApplication);

		ImGui_ImplSdlGL3_NewFrame(gWindow);
		// Update
		if (showWindow)
		{
			ImGui::Begin("Window", &showWindow);
			ImGui::Text("Hello world");
			if (ImGui::Button("Close me"))
				showWindow = false;
			ImGui::End();
		}

		// Update physics
		PhysicsSettings::Instance().World()->stepSimulation(1.0f / 60.0f, 10);

		bob->UpdateInput();
		bob->UpdatePhysics();

		// Render
		glClearColor(1.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::for_each(m_graphicsComponents.begin(), m_graphicsComponents.end(), [](GraphicsComponent* _g) {_g->Update(); });

		ImGui::Render();
		ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());

		// Update the surface
		SDL_GL_SwapWindow(gWindow);
	}

	delete bob;
	bob = nullptr;

	delete camera;
	camera = nullptr;

	PhysicsSettings::DestroyInstance();

	// Cleanup imgui
	ImGui_ImplSdlGL3_Shutdown();
	ImGui::DestroyContext();

	// Free resources and close SDL
	CloseSDL();

	return 0;
}

