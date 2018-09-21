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

	glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 0.0f);
	GLuint simpleProgram = sl.CreateProgram("Assets/Shaders/Vertex/Simple.vs", "Assets/Shaders/Fragment/Simple.fs");
	GLuint program = sl.CreateProgram("Assets/Shaders/Vertex/SimpleLighting.vs", "Assets/Shaders/Fragment/SimpleLighting.fs");
	GLuint debugProgram = sl.CreateProgram("Assets/Shaders/Vertex/Debug.vs", "Assets/Shaders/Fragment/SimpleLighting.fs");

	m_physicsRenderer = new PhysicsDebugRenderer();
	m_physics->World()->setDebugDrawer(m_physicsRenderer);

	camera = new Camera();
	camera->m_transform->position = glm::vec3(0.0f, 0.0f, 6.0f);
	light = new Light(lightPos);

	GLuint skyboxProgram = sl.CreateProgram("Assets/Shaders/Vertex/CubeMap.vs", "Assets/Shaders/Fragment/CubeMap.fs");
	std::vector<std::string> skyBoxTextures;
	skyBoxTextures.push_back("Assets/Textures/Skybox/right.jpg");
	skyBoxTextures.push_back("Assets/Textures/Skybox/left.jpg");
	skyBoxTextures.push_back("Assets/Textures/Skybox/top.jpg");
	skyBoxTextures.push_back("Assets/Textures/Skybox/bottom.jpg");
	skyBoxTextures.push_back("Assets/Textures/Skybox/back.jpg");
	skyBoxTextures.push_back("Assets/Textures/Skybox/front.jpg");
	GameObject* skybox = new GameObject("Skybox", camera, nullptr, new ShapeGraphicsComponent(ModelType::SKYBOXSHAPE), nullptr, nullptr);
	skybox->SetScale(glm::vec3(100.0f));
	skybox->Initialise(skyboxProgram);
	skybox->SetTextures(skyBoxTextures);
	m_gameObjects.insert(std::pair<GAMEOBJECTNAME, GameObject*>(GAMEOBJECTNAME::SKYBOX, skybox));
	m_graphicsComponents.push_back(skybox->GetGraphicsComponent());

	GameObject* ground = new GameObject("Ground", camera, light, new ShapeGraphicsComponent(CUBE), nullptr, new StaticPhysicsComponent(0.0f));
	ground->Initialise(program);
	ground->SetTexture("Assets/Textures/grass.jpg");
	ground->SetScale(glm::vec3(50.0f, 1.0f, 50.0f));
	m_graphicsComponents.push_back(ground->GetGraphicsComponent());
	m_physics->AddCollisionShape(ground->GetPhysicsComponent()->GetCollisionShape());
	m_physics->World()->addRigidBody(ground->GetPhysicsComponent()->GetRigidBody());
	m_physics->World()->updateSingleAabb(ground->GetPhysicsComponent()->GetRigidBody());
	m_gameObjects.insert(std::pair<GAMEOBJECTNAME, GameObject*>(GROUND, ground));

	bob = new GameObject("Box", camera, light, new ShapeGraphicsComponent(CUBE), nullptr, new StaticPhysicsComponent(1.0f));
	bob->Initialise(program);
	bob->SetTexture("Assets/Textures/rayman.jpg");
	bob->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
	m_gameObjects.insert(std::pair<GAMEOBJECTNAME, GameObject*>(BOX, bob));
	m_graphicsComponents.push_back(bob->GetGraphicsComponent());
	m_physics->AddCollisionShape(bob->GetPhysicsComponent()->GetCollisionShape());
	m_physics->World()->addRigidBody(bob->GetPhysicsComponent()->GetRigidBody());
	m_physicsComponents.push_back(bob->GetPhysicsComponent());

	GameObject* cameraController = new GameObject("Camera Controller", camera, nullptr, nullptr, new ThirdPersonCameraInputComponent(bob), nullptr);
	cameraController->Initialise();
	m_gameObjects.insert(std::pair<GAMEOBJECTNAME, GameObject*>(CAMERA_CONTROLLER, cameraController));
	m_inputComponents.push_back(cameraController->GetInputComponent());

	GameObject* lightBox = new GameObject("Light box", camera, nullptr, new ShapeGraphicsComponent(CUBE), nullptr, nullptr);
	lightBox->Initialise(simpleProgram);
	lightBox->SetPosition(lightPos);
	m_gameObjects.insert(std::pair<GAMEOBJECTNAME, GameObject*>(LIGHT_BOX, lightBox));
	m_graphicsComponents.push_back(lightBox->GetGraphicsComponent());
}

void Game::Initialise()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC);
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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

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

		// Input Event Handler
		m_input->Update(m_closeApplication);

		ImGui_ImplSdlGL3_NewFrame(m_Window);
		// Update imgui
		if (m_showWindow)
		{
			ImGui::Begin("Window", &m_showWindow);
			ImGui::Text(m_gameObjects[BOX]->GetName().c_str());
			//ImGui::InputFloat("x", &m_gameObjects[BOX]->GetPosition().x);
			//ImGui::InputFloat("y", &m_gameObjects[BOX]->GetTransform()->position.y);
			//ImGui::InputFloat("z", &m_gameObjects[BOX]->GetTransform()->position.z);
			if (ImGui::Button("Save"))
			{
				// TODO: save values to .ini file
			}
			ImGui::End();
		}
		
		// Update Input Components
		std::for_each(m_inputComponents.begin(), m_inputComponents.end(), [](InputComponent* _i) { _i->Update(); });

		// Toggle Cursor
		if (m_input->GetKeyPress(SDL_SCANCODE_ESCAPE))
			SDL_SetRelativeMouseMode(static_cast<SDL_bool>(!SDL_GetRelativeMouseMode()));

		// Update physics
		m_physics->World()->stepSimulation(1.0f / 60.0f, 10);
		for (int i = m_physics->World()->getNumCollisionObjects() - 1; i >= 0; --i)
		{
			btCollisionObject* obj = m_physics->World()->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(trans);
			}
			else
			{
				trans = obj->getWorldTransform();
			}
			printf("world pos object %d = %f,%f,%f\n", i, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		}

		std::for_each(m_physicsComponents.begin(), m_physicsComponents.end(), [](PhysicsComponent* _p) {_p->Update(); });

		if (m_input->GetKeyPress(SDL_SCANCODE_SPACE))
		{
			m_gameObjects[BOX]->SetPosition(glm::vec3(0.0f, 5.0f, 0.0f));
		}

		// Render
		glClearColor(1.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_physicsRenderer->SetMatrices(camera->View(), camera->Projection());
		m_physics->World()->debugDrawWorld();

		std::for_each(m_graphicsComponents.begin(), m_graphicsComponents.end(), [](GraphicsComponent* _g) {_g->Update(); });

		ImGui::Render();
		ImGui_ImplSdlGL3_RenderDrawData(ImGui::GetDrawData());

		// Update the surface
		SDL_GL_SwapWindow(m_Window);
	}
}

void Game::ShutDown()
{
	delete camera;
	camera = nullptr;
	delete light;
	light = nullptr;

	delete m_physics;
	m_physics = nullptr;
	delete m_sceneManager;
	m_sceneManager = nullptr;
	delete m_input;
	m_input = nullptr;
	delete m_physicsRenderer;
	m_physicsRenderer = nullptr;

	for (auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); ++iter)
	{
		delete iter->second;
		iter->second = nullptr;
	}

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
