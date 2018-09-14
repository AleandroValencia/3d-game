//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include "Dependencies\glew\glew.h"
#include "Dependencies\sdl\include\SDL_opengl.h"

#include "Dependencies\Bullet\include\btBulletDynamicsCommon.h"
#include "Dependencies\Dear_ImGui\imgui.h"
#include "Dependencies\Dear_ImGui\imgui_impl_sdl_gl3.h"

#include "SceneManager.h"

// --Global Variables--
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const char* gTitle = "3D Game";
SDL_Window* gWindow = nullptr;
SDL_GLContext gContext = nullptr;
bool vSync = true;

Uint64 currentTime = SDL_GetPerformanceCounter();
Uint64 elapsedTime = 0;
double deltaTime = 0;

SceneManager* SceneManager::s_SceneManager = nullptr;

bool InitSDL()
{
	bool success = true;

	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	delete collisionConfiguration;
	collisionConfiguration = nullptr;

	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialise! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Create Window
		gWindow = SDL_CreateWindow(gTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
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
			InitImGui();
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

				// Render
				glClearColor(1.0, 0.0, 0.0, 1.0);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				ImGui::Render();
				ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());
				// Update the surface
				SDL_GL_SwapWindow(gWindow);
			}
		}
	}

	// Free resources and close SDL
	CloseSDL();

	return 0;
}

