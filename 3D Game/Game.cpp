#include "Game.h"

Game* Game::m_instance = nullptr;

Game::Game() {}
Game::~Game() {}

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
	ShaderLoader sl;

	camera = new Camera();

	GLuint skyboxProgram = sl.CreateProgram("Assets/Shaders/Vertex/CubeMap.vs", "Assets/Shaders/Fragment/CubeMap.fs");
	std::vector<std::string> skyBoxTextures;
	skyBoxTextures.push_back("Assets/Textures/Skybox/right.jpg");
	skyBoxTextures.push_back("Assets/Textures/Skybox/left.jpg");
	skyBoxTextures.push_back("Assets/Textures/Skybox/top.jpg");
	skyBoxTextures.push_back("Assets/Textures/Skybox/bottom.jpg");
	skyBoxTextures.push_back("Assets/Textures/Skybox/back.jpg");
	skyBoxTextures.push_back("Assets/Textures/Skybox/front.jpg");
	GameObject* skybox = new GameObject(camera, new ShapeGraphicsComponent(SKYBOX), nullptr, nullptr);
	skybox->GetTransform()->scale = glm::vec3(100.0f);
	skybox->Initialise(skyboxProgram);
	skybox->SetTextures(skyBoxTextures);
	m_gameObjects.push_back(skybox);
	m_graphicsComponents.push_back(skybox->GetGraphicsComponent());

	GLuint program = sl.CreateProgram("Assets/Shaders/Vertex/Texture.vs", "Assets/Shaders/Fragment/Texture.fs");
	bob = new GameObject(camera, new ShapeGraphicsComponent(TRIANGLE), nullptr, nullptr);
	bob->Initialise(program);
	bob->SetTexture("Assets/Textures/Grass.jpg");
	m_gameObjects.push_back(bob);
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
	SDL_SetRelativeMouseMode(SDL_TRUE);	// Get relative motion data in SDL_MOUSEMOTION event.

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplSdlGL3_Init(m_Window);
	ImGui::StyleColorsDark();

	m_physics = new PhysicsSettings();
	m_sceneManager = new SceneManager();
	m_input = new InputHandler();

	InitGameObjects();
}

void Game::MainLoop()
{
	while (!m_closeApplication)
	{
		// Calculate Delta Time
		Uint64 elapsedTime = m_currentTime;
		m_currentTime = SDL_GetPerformanceCounter();
		float deltaTime = static_cast<float>((m_currentTime - elapsedTime) * 1000 / static_cast<float>(SDL_GetPerformanceFrequency()));
		deltaTime = deltaTime * 0.001f;	// Convert ms to s

		// Input events
		m_input->Update(m_closeApplication);

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

		if (m_input->GetKeyHold(SDL_SCANCODE_W))
		{
			camera->MoveForward();
		}
		else if (m_input->GetKeyHold(SDL_SCANCODE_S))
		{
			camera->MoveBackward();
		}
		if (m_input->GetKeyHold(SDL_SCANCODE_A))
		{
			camera->MoveLeft();
		}
		else if (m_input->GetKeyHold(SDL_SCANCODE_D))
		{
			camera->MoveRight();
		}

		glm::vec3 rotation = glm::vec3(m_input->GetYOffset(), m_input->GetXOffset(), 0.0f);
		//camera->Rotate(rotation);
		camera->RotateAround(*(bob->GetTransform()), rotation);

		// Toggle Cursor
		if (m_input->GetKeyPress(SDL_SCANCODE_ESCAPE))
			SDL_SetRelativeMouseMode(static_cast<SDL_bool>(!SDL_GetRelativeMouseMode()));

		// Update physics
		m_physics->World()->stepSimulation(1.0f / 60.0f, 10);

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

void Game::ShutDown()
{
	for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); ++iter)
	{
		delete *iter;
		*iter = nullptr;
	}

	delete camera;
	camera = nullptr;

	delete m_physics;
	m_physics = nullptr;
	delete m_sceneManager;
	m_sceneManager = nullptr;
	delete m_input;
	m_input = nullptr;

	// Cleanup imgui
	ImGui_ImplSdlGL3_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(m_Context);
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();

	delete m_instance;
	m_instance = nullptr;
}
