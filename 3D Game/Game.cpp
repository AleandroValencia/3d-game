#include "Game.h"

Game* Game::m_instance = nullptr;

Game::Game(){}
Game::~Game(){}

Game & Game::Instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Game();
	}
	return *m_instance;
}

void Game::InitGameObjects()
{
	camera = new Camera();
	ShaderLoader sl;
	GLuint program = sl.CreateProgram("Assets/Shaders/Vertex/Texture.vs", "Assets/Shaders/Fragment/Texture.fs");
	bob = new GameObject(camera, new ShapeGraphicsComponent(), nullptr, nullptr);
	bob->Initialise(program);
	bob->SetTexture("Assets/Textures/Grass.jpg");
	m_graphicsComponents.push_back(bob->GetGraphicsComponent());
}

void Game::Initialise()
{
	SDL_Init(SDL_INIT_VIDEO);
	m_Window = SDL_CreateWindow(m_Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Utils::WIDTH, Utils::HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	m_Context = SDL_GL_CreateContext(m_Window);
	glewInit();
	if (m_vSync)
	{
		SDL_GL_SetSwapInterval(1);
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplSdlGL3_Init(m_Window);
	ImGui::StyleColorsDark();

	InitGameObjects();
}

void Game::MainLoop()
{
	while (!m_closeApplication)
	{
		// Calculate Delta Time
		float elapsedTime = m_currentTime;
		m_currentTime = SDL_GetPerformanceCounter();
		float deltaTime = static_cast<double>((m_currentTime - elapsedTime) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency()));
		deltaTime = deltaTime * 0.001f;	// Convert ms to s

		HandleEvents(e, m_closeApplication);

		ImGui_ImplSdlGL3_NewFrame(m_Window);
		// Update
		if (m_showWindow)
		{
			ImGui::Begin("Window", &m_showWindow);
			ImGui::Text("Hello world");
			if (ImGui::Button("Close me"))
				m_showWindow = false;
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
		SDL_GL_SwapWindow(m_Window);
	}
}

void Game::HandleEvents(SDL_Event & _e, bool & _quit)
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

void Game::ShutDown()
{
	delete bob;
	bob = nullptr;

	delete camera;
	camera = nullptr;

	PhysicsSettings::DestroyInstance();

	// Cleanup imgui
	ImGui_ImplSdlGL3_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(m_Context);
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}
