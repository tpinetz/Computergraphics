#include "Scene.h"

namespace Scene {

	Scene::Scene(GLFWwindow* window, float right, float top) {
		m_right = right;
		m_top = top;
		this->window = window;
	}


	Scene::~Scene()
	{
	}


	bool Scene::init(std::string levelFileName) {
		// It is important that the Physics is initialized first.
		return initPhysics()
			&& initInternalObjects()
			&& addSceneRelevantGameObjects()
			&& addLevelDependantObjects(levelFileName)
			&& addTransparentGameObjects();
	}

	bool Scene::initPhysics() {
		//m_physicsWorld = std::shared_ptr<Physics::PhysicsWorld>(new Physics::PhysicsWorld());
		m_physicsWorld = new Physics::PhysicsWorld();
		return m_physicsWorld->initPhysics();
	}

	bool Scene::initInternalObjects() {
		// Shader Initiliazition

		this->shaderHelper = std::shared_ptr<ShaderHelper>(new ShaderHelper());
		if (!this->shaderHelper->loadShader("../DefendyourTUItion/VertexShader.vertexshader", "../DefendyourTUItion/fragmentShader.fragmentshader")) {
			std::cerr << "Failed to read Shader";
			return false;
		}

		this->m_textureShader = std::shared_ptr<ShaderHelper>(new ShaderHelper());
		if (!this->m_textureShader->loadShader("../DefendyourTUItion/TextureShader.vertexshader", "../DefendyourTUItion/TextureShader.fragmentshader")) {
			std::cerr << "Failed to read Shader";
			return false;
		}

		this->m_skyboxShader = std::shared_ptr<ShaderHelper>(new ShaderHelper());
		if (!this->m_skyboxShader->loadShader("../DefendyourTUItion/SkyboxShader.vertexshader", "../DefendyourTUItion/SkyboxShader.fragmentshader")) {
			std::cerr << "Failed to read Shader";
			return false;
		}

		this->m_meshShader = std::shared_ptr<ShaderHelper>(new ShaderHelper());
		if (!this->m_meshShader->loadShader("../DefendyourTUItion/MeshShader.vertexshader", 
			"../DefendyourTUItion/MeshShader.fragmentshader")) {
			std::cerr << "Failed to read Shader";
			return false;
		}

		this->m_particleShader = std::shared_ptr<ShaderHelper>(new ShaderHelper());
		if (!this->m_particleShader->loadShader("../DefendyourTUItion/ParticleShader.vertexshader",
			"../DefendyourTUItion/ParticleShader.fragmentshader")) {
			std::cerr << "Failed to read Shader";
			return false;
		}

		this->m_textShader = std::shared_ptr<ShaderHelper>(new ShaderHelper());
		if (!this->m_textShader->loadShader("../DefendyourTUItion/TextShader.vertexshader",
			"../DefendyourTUItion/TextShader.fragmentshader")) {
			std::cerr << "Failed to read Shader";
			return false;
		}

		this->m_shadowShader = std::shared_ptr<ShaderHelper>(new ShaderHelper());
		if (!this->m_shadowShader->loadShader("../DefendyourTUItion/ShadowShader.vertexshader",
			"../DefendyourTUItion/ShadowShader.fragmentshader")) {
			std::cerr << "Failed to read Shader";
			return false;
		}

		this->m_depthTestShader = std::shared_ptr<ShaderHelper>(new ShaderHelper());
		if (!this->m_depthTestShader->loadShader("../DefendyourTUItion/DepthMapTest.vertexshader",
			"../DefendyourTUItion/DepthMapTest.fragmentshader")) {
			std::cerr << "Failed to read Shader";
			return false;
		}

		//Input Initialization

		m_keyboardManager = Input::KeyboardManager::getKeyboardManager();
		m_mouseInputManager = Input::MouseInputManager::getMouseInputManagerInstance();

		// Game Object Manager Initialization

		m_gameObjectManager = std::shared_ptr<GameObjectManager::GameObjectManager>(new GameObjectManager::GameObjectManager());
		m_extraGameObjectManager = std::shared_ptr < GameObjectManager::GameObjectManager>(
			new GameObjectManager::GameObjectManager()
			);

		m_camera = std::shared_ptr<Camera::Camera>(
			new Camera::Camera(m_keyboardManager, m_right, m_top));

		m_mouseInputManager->setCamera(m_camera);

		m_time = glfwGetTime();

		glfwSetKeyCallback(window, Input::KeyboardManager::key_callback);
		glfwSetCursorPosCallback(window, Input::MouseInputManager::mouse_callback);
		glfwSetMouseButtonCallback(window, Input::MouseInputManager::mouse_button_callback);

		m_renderer = std::shared_ptr<Renderer::Renderer>(new Renderer::Renderer());
		m_renderer->init();

		m_sun = std::shared_ptr<GameObject::DirectionalLight>(
			new GameObject::DirectionalLight(
			shaderHelper->getProgramId(),
			glm::vec3(-0.2, -1.0f, -0.3f),
			glm::vec3(0.15f, 0.15f, 0.15f),
			glm::vec3(0.4f, 0.4f, 0.4f),
			glm::vec3(0.5f, 0.5f, 0.5f)
			));
		m_gameObjectManager->addObject(m_sun);
		m_renderer->setDirectionalLight(m_sun->getRenderData());
		return true;
	}

	bool Scene::addSceneRelevantGameObjects() {
		auto skybox = std::shared_ptr<GameObject::SkyBox>(
			new GameObject::SkyBox(m_skyboxShader->getProgramId()));
		m_gameObjectManager->addObject(skybox);
		
		m_rockModel = std::shared_ptr<ModelLoader>(new ModelLoader());
		m_rockModel->loadModel("../Assets/Model/rock/rock.obj");
		auto avatar = std::shared_ptr<GameObject::PhysicsObject>(
			new GameObject::Avatar(m_camera,
			m_physicsWorld,
			m_extraGameObjectManager,
			m_textureShader->getProgramId(), m_rockModel, m_particleShader->getProgramId()));
		m_gameObjectManager->addObject(avatar);
		m_physicsWorld->addPhysicsObject(avatar);
		
	auto ground = std::shared_ptr<GameObject::Ground>(new GameObject::Ground(m_textureShader->getProgramId(), 
		233, 233));
		m_gameObjectManager->addObject(ground);
		m_physicsWorld->addPhysicsObject(ground);

		glm::mat4 trans =
			glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f)) *								//scale to world dimensions
			glm::rotate(glm::mat4(), 90.0f * 3.1416f / 180.0f, glm::vec3(0.0f, 1.0f, 0.0f)) *
			glm::rotate(glm::mat4(), 90.0f * 3.1416f / 180.0f, glm::vec3(-1.0f, 0.0f, 0.0f)) *		//rotate
			glm::scale(glm::mat4(1.0f), glm::vec3(0.011637)) *										//make it unitary
			glm::translate(glm::mat4(1.0f), glm::vec3(7.24348, 1.70471, -40.0434));					//center object
		mod.LoadModel("../Assets/Model/warrior/warrior.md2", trans);
		
		std::shared_ptr<ModelLoader> treeModel = std::shared_ptr<ModelLoader>(new ModelLoader());
		treeModel->loadModel("../Assets/Model/Tree1/Tree.obj");


		auto tree = std::shared_ptr<GameObject::Obstacle>(new GameObject::Obstacle(
			treeModel, m_meshShader->getProgramId(), glm::vec3(10.0f, 0.0f, -10.0f), 
			glm::vec3(0.5f, 1.0f, 0.5f)));
		m_gameObjectManager->addObject(tree);
		m_physicsWorld->addPhysicsObject(tree);

		std::shared_ptr<GameObject::Light> light = std::shared_ptr<GameObject::Light>(
			new GameObject::Light(
			glm::vec3(0.0f, 15.0f, 50.0f),      // Position
			shaderHelper->getProgramId(),	// Shader
			glm::vec3(0.2f,0.2f,0.2f),		// Ambient Light Color
			glm::vec3(1.0f, 1.0f, 1.0f),	// Diffuse Light Color
			glm::vec3(0.5f, 0.5f, 0.5f)		// Specular Light Color
			));


		m_gameObjectManager->addObject(light);
		m_renderer->addLight(light->getRenderData());
		m_renderer->setCamera(m_camera);

		return true;
	}

	bool Scene::addLevelDependantObjects(std::string levelFileName) {
		printf("Loading Level file %s...\n", levelFileName.c_str());

		FILE * file = fopen(levelFileName.c_str(), "r");
		if (file == NULL){
			char cCurrentPath[FILENAME_MAX];

			getcwd(cCurrentPath, sizeof(cCurrentPath));

			printf("Impossible to open %s. Are you in the right directory ? You are in %s. Don't forget to read the FAQ !\n", levelFileName, cCurrentPath);
			getchar();
			return false;
		}

		while (1){

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF) {
				break; // EOF = End Of File. Quit the loop.
			}
			// else : parse lineHeader

			if (strcmp(lineHeader, "e") == 0){
				glm::vec3 enemyPosition;
				fscanf(file, "%f %f %f\n", &enemyPosition.x, &enemyPosition.y, &enemyPosition.z);
				auto enemy = std::shared_ptr<GameObject::Enemy>(
					new GameObject::Enemy("enemy5", enemyPosition,
					m_meshShader->getProgramId(), mod));
				m_gameObjectManager->addObject(enemy);
				m_physicsWorld->addPhysicsObject(enemy);
				m_enemies.push_back(enemy);
			}
			else{
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}

		}

		fclose(file);

		return true;
	}

	bool Scene::addTransparentGameObjects() {
		m_podest = std::shared_ptr<GameObject::Podest>(
			new GameObject::Podest(m_textureShader->getProgramId(),
			Common::ModelLoaderHelper::getInstance()->getTextureModel("../Assets/Model/Podest/Podest.obj",
			"../Assets/Textures/paving/paving01.jpg",
			"../Assets/Textures/paving/paving01b.jpg",
			"../Assets/Textures/paving/paving01s.jpg")));
		m_gameObjectManager->addObject(m_podest);
		return true;
	}

	bool Scene::runIntro(std::string level) {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		do {
			glfwPollEvents();


			m_renderer->beginDrawing(this->window, m_right, m_top);
			m_renderer->startShader(m_textShader->getProgramId());
			m_renderer->drawText("Please press space to start" , 250.f, 400.f, 1.f, glm::vec3(0.5, 0.5f, 0.5f));
			m_renderer->drawText("Level: " + level, 340.f, 350.f, 1.f, glm::vec3(0.5, 0.5f, 0.5f));
			m_renderer->stopShader();
			m_renderer->endDrawing(this->window);

			if (m_keyboardManager->isKeyPressed(GLFW_KEY_SPACE)) {
				return true;
			}

		} while (!m_keyboardManager->isKeyPressed(GLFW_KEY_ESCAPE) && 
			glfwWindowShouldClose(this->window) == 0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		m_physicsWorld->cleanUp();
		m_enemies.clear();
		m_renderer->stopShader();
		delete m_physicsWorld;

		return false;
	}



	void Scene::runOutro(std::string level, bool won) {
		glfwPollEvents();


		m_renderer->beginDrawing(this->window, m_right, m_top);
		m_renderer->startShader(m_textShader->getProgramId());
		if (won) {
			m_renderer->drawText("Congrats you successfully beat ", 250.f, 400.f, 1.f, glm::vec3(0.5, 0.5f, 0.5f));
		}
		else {
			m_renderer->drawText("Unfortunately you lost at", 250.f, 400.f, 1.f, glm::vec3(0.5, 0.5f, 0.5f));
		}
		m_renderer->drawText("Level: " + level, 340.f, 350.f, 1.f, glm::vec3(0.5, 0.5f, 0.5f));
		m_renderer->stopShader();
		m_renderer->endDrawing(this->window);

	}

	bool Scene::run() {
		double time = glfwGetTime();

		double deltaTime = time - m_time;
		m_time = time;
		bool won = true;
		int numEnemies = 0;
		int nbFrames = 0;
		int frames = 0;
		double lastTime = 1.0f;
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);

		do {
			glfwPollEvents();
			time = glfwGetTime();
			deltaTime = time - m_time;
			m_time = time;

			
			m_physicsWorld->runPhysics(deltaTime);
			
			changeSettings(deltaTime);
			m_gameObjectManager->update(deltaTime);
			m_renderer->preShadowDraw();
			m_gameObjectManager->renderShadows(m_renderer, m_shadowShader->getProgramId());
			m_renderer->postShadowDraw();
			
			m_renderer->beginDrawing(this->window, m_right, m_top);
			m_gameObjectManager->render(m_renderer);

			m_renderer->startShader(m_textShader->getProgramId());
			m_renderer->drawText("There are " + std::to_string(numEnemies) + " Enemies left", 0.5f, 0.5f, 1.0f, glm::vec3(0.0, 0.0f, 0.0f));
			if (frameTime) {
				std::string frameString = std::to_string(1.0f / deltaTime);
				cout << frameString << std::endl;
				m_renderer->drawText(frameString + " FPS", 0.0f, m_top - 48.0f, 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			}
			m_renderer->stopShader();

//			m_renderer->debugDepthMap(m_depthTestShader->getProgramId());

			m_renderer->endDrawing(this->window);

			for (auto newGameObject : m_extraGameObjectManager->getGameObjects()) {
				m_gameObjectManager->addObjectFront(newGameObject);
			}
			if (!m_extraGameObjectManager->getGameObjects().empty()) {
				m_extraGameObjectManager->getGameObjects().clear();
			}
			

			won = true;
			bool lost = false;
			numEnemies = 0;
			for (auto enemy : m_enemies) {
				if (!enemy->isDead()) {
					won = false;
					numEnemies++;
				}
				if (glm::abs(enemy->getPosition().x) < 0.2 &&
					glm::abs(enemy->getPosition().y) < 0.2 &&
					glm::abs(enemy->getPosition().z) < 0.2) {
					lost = true;
				}
			}

			if (won) {
				std::cout << "Game is won!" << std::endl;
				break;
			}
			else if (lost) {
				std::cout << "Game is lost!" << std::endl;
				break;
			}

			

		} while (!m_keyboardManager->isKeyPressed(GLFW_KEY_ESCAPE) &&
			glfwWindowShouldClose(this->window) == 0);
		
		m_physicsWorld->cleanUp();
		m_enemies.clear();
		m_renderer->stopShader();
		delete m_physicsWorld;

		return won;
	}

	void Scene::changeSettings(float deltaTime) {
		static float fTimer = 0.0f;

		fTimer -= deltaTime;
		if (m_keyboardManager->isKeyPressed(GLFW_KEY_F2) && fTimer < 0.0f) {
			frameTime = !frameTime;
			std::cout << "Frametime is turned " << (frameTime ? "on" : "off") << std::endl;
			fTimer = 0.1f;
		}

		if (m_keyboardManager->isKeyPressed(GLFW_KEY_F3) && fTimer < 0.0f) {
			if (!wireframeMode) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			wireframeMode = !wireframeMode;
			std::cout << "Wireframe mode is turned " << (wireframeMode ? "on" : "off") << std::endl;
			fTimer = 0.1f;
		}

		if (m_keyboardManager->isKeyPressed(GLFW_KEY_F9) && fTimer < 0.0f) {
			if (!transparentMode) {
				m_podest->setAlpha(0.3f);
			}
			else {
				m_podest->setAlpha(1.0f);
			}

			transparentMode = !transparentMode;
			fTimer = 0.1f;
		}
	}
}