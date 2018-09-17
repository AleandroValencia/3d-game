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

#include "Camera.h"
#include "GameObject.h"
#include "ShapeGraphicsComponent.h"
#include "ShaderLoader.h"

// --Global Variables--
btDefaultCollisionConfiguration* collisionConfiguration = nullptr;
btCollisionDispatcher* dispatcher = nullptr;
btBroadphaseInterface* overlappingPairCache = nullptr;
btSequentialImpulseConstraintSolver* solver = nullptr;
btDiscreteDynamicsWorld* dynamicsWorld = nullptr;
const char* gTitle = "3D Game";
SDL_Window* gWindow = nullptr;
SDL_GLContext gContext;
bool vSync = true;

Uint64 currentTime = SDL_GetPerformanceCounter();
Uint64 elapsedTime = 0;
double deltaTime = 0;

SceneManager* SceneManager::s_SceneManager = nullptr;

GameObject* bob;
Camera* camera;

std::vector<GraphicsComponent*> m_graphicsComponents;

bool InitSDL()
{
	bool success = true;

	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create Window
		gWindow = SDL_CreateWindow(gTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Utils::WIDTH, Utils::HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create context
			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialise GLEW
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					printf("Error initialising GLEW! %s\n", glewGetErrorString(glewError));
				}

				// Use Vsync
				if (vSync)
				{
					if (SDL_GL_SetSwapInterval(1) < 0)
					{
						printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
					}
				}
			}
		}
	}

	return success;
}

void CloseSDL()
{
	SDL_GL_DeleteContext(gContext);
	// Destroy Window
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	// Quit SDL subsystems
	SDL_Quit();
}

void InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
	ImGui_ImplSdlGL3_Init(gWindow);
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them. 
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple. 
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'misc/fonts/README.txt' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);
}

void InitBullet()
{
	overlappingPairCache = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

	// Cleanup physics
	//remove the rigidbodies from the dynamics world and delete them
	if (dynamicsWorld != nullptr)
	{
		for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}
	}
	delete collisionConfiguration;
	collisionConfiguration = nullptr;
	delete dispatcher;
	dispatcher = nullptr;
	delete solver;
	solver = nullptr;
	delete overlappingPairCache;
	overlappingPairCache = nullptr;
	delete dynamicsWorld;
	dynamicsWorld = nullptr;
}

void HandleEvents(SDL_Event& _e, bool& _quit)
{
	while (SDL_PollEvent(&_e) != 0)
	{
		ImGui_ImplSdlGL3_ProcessEvent(&_e);
		// User requests quit
		if (_e.type == SDL_QUIT)
		{
			_quit = true;
		}
		// User presses a key
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
}

int main(int argc, char* args[])
{
	srand(static_cast<unsigned int>(time(NULL)));

	bool closeApplication = false;
	SDL_Event e;

	bool showWindow = true;

	if (!InitSDL())
	{
		printf("Failed to Initialise!\n");
	}
	else
	{
		if (SceneManager::Instance().Initialise() == false)
		{
			printf("Failed to initialise\n");
		}
		else
		{
			InitBullet();
			InitImGui();
			Init();
			glClearColor(0.0, 0.0, 0.0, 1.0);
			while (!closeApplication)
			{
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
				//dynamicsWorld->stepSimulation(1.0f / 60.0f, 10);

				bob->UpdateInput();
				bob->UpdatePhysics();

				// Render
				glClearColor(1.0, 0.0, 0.0, 1.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				bob->Render();

				ImGui::Render();
				ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());

				// Update the surface
				SDL_GL_SwapWindow(gWindow);
			}
		}
	}

	delete bob;
	bob = nullptr;

	delete camera;
	camera = nullptr;

	SceneManager::DestroyInstance();

	std::for_each(m_graphicsComponents.begin(), m_graphicsComponents.end(), [](GraphicsComponent* _g) { delete _g; _g = nullptr; });

	 //Cleanup physics
	//remove the rigidbodies from the dynamics world and delete them
	if (dynamicsWorld != nullptr)
	{
		for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}
	}
	delete collisionConfiguration;
	collisionConfiguration = nullptr;
	delete dispatcher;
	dispatcher = nullptr;
	delete solver;
	solver = nullptr;
	delete overlappingPairCache;
	overlappingPairCache = nullptr;
	delete dynamicsWorld;
	dynamicsWorld = nullptr;

	// Cleanup imgui
	ImGui_ImplSdlGL3_Shutdown();
	ImGui::DestroyContext();

	// Free resources and close SDL
	CloseSDL();

	return 0;
}

