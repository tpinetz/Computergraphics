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
			&& addLevelDependantObjects(levelFileName);
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

		this->m_meshShader = std::shared_ptr<ShaderHelper>(new ShaderHelper());
		if (!this->m_meshShader->loadShader("../DefendyourTUItion/MeshShader.vertexshader", 
			"../DefendyourTUItion/MeshShader.fragmentshader")) {
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

		m_sun = std::shared_ptr<GameObject::DirectionalLight>(
			new GameObject::DirectionalLight(
			shaderHelper->getProgramId(),
			glm::vec3(-0.2, -1.0f, -0.3f),
			glm::vec3(0.05f, 0.05f, 0.05f),
			glm::vec3(0.4f, 0.4f, 0.4f),
			glm::vec3(0.5f, 0.5f, 0.5f)
			));
		m_gameObjectManager->addObject(m_sun);
		m_renderer->setDirectionalLight(m_sun->getRenderData());
		return true;
	}

	bool Scene::addSceneRelevantGameObjects() {
		m_gameObjectManager->addObject(
			std::shared_ptr<GameObject::GameObject>(
			new GameObject::Avatar(m_camera, 
				m_physicsWorld,
				m_extraGameObjectManager, 
				m_textureShader->getProgramId())));

		
	auto ground = std::shared_ptr<GameObject::Ground>(new GameObject::Ground(m_textureShader->getProgramId(), 
		233, 233));
		m_gameObjectManager->addObject(ground);
		m_physicsWorld->addPhysicsObject(ground);

		auto podest = std::shared_ptr<GameObject::Podest>(
			new GameObject::Podest(m_textureShader->getProgramId(),
			Common::ModelLoaderHelper::getInstance()->getTextureModel("../Assets/Model/Podest/Podest.obj", 
			"../Assets/Textures/paving/paving01b.jpg",
			"../Assets/Textures/paving/paving01s.jpg")));
		m_gameObjectManager->addObject(podest);

		mod.loadModel("../Assets/Model/nanosuit/nanosuit.obj");
		
/*		auto enemy1 = std::shared_ptr<GameObject::Enemy>(
			new GameObject::Enemy("enemy1", glm::vec3(1, 1, -10), 
			m_meshShader->getProgramId(), mod));
		m_gameObjectManager->addObject(enemy1);
		m_physicsWorld->addPhysicsObject(enemy1);
		m_enemies.push_back(enemy1);

		auto enemy2 = std::shared_ptr<GameObject::Enemy>(
			new GameObject::Enemy("enemy2", glm::vec3(5, 1, -13),
			m_meshShader->getProgramId(), mod));
		m_gameObjectManager->addObject(enemy2);
		m_physicsWorld->addPhysicsObject(enemy2);
		m_enemies.push_back(enemy2);

		auto enemy3 = std::shared_ptr<GameObject::Enemy>(
			new GameObject::Enemy("enemy3", glm::vec3(-5, 1, -20),
			m_meshShader->getProgramId(), mod));
		m_gameObjectManager->addObject(enemy3);
		m_physicsWorld->addPhysicsObject(enemy3);
		m_enemies.push_back(enemy3);

		auto enemy4 = std::shared_ptr<GameObject::Enemy>(
			new GameObject::Enemy("enemy4", glm::vec3(0, 1, -23),
			m_meshShader->getProgramId(), mod));
		m_gameObjectManager->addObject(enemy4);
		m_physicsWorld->addPhysicsObject(enemy4);
		m_enemies.push_back(enemy4);
		

		auto enemy5 = std::shared_ptr<GameObject::Enemy>(
			new GameObject::Enemy("enemy5", glm::vec3(10, 1, -27),
			m_meshShader->getProgramId(), mod));
		m_gameObjectManager->addObject(enemy5);
		m_physicsWorld->addPhysicsObject(enemy5);
		m_enemies.push_back(enemy5);*/

		std::shared_ptr<GameObject::Light> light = std::shared_ptr<GameObject::Light>(
			new GameObject::Light(
			glm::vec3(1.2f, 1.0f, -3.0f),      // Position
			shaderHelper->getProgramId(),	// Shader
			glm::vec3(0.2f,0.2f,0.2f),		// Ambient Light Color
			glm::vec3(1.0f, 1.0f, 1.0f),	// Diffuse Light Color
			glm::vec3(0.5f, 0.5f, 0.5f)		// Specular Light Color
			));


		m_gameObjectManager->addObject(light);
		m_renderer->addLight(light->getRenderData());

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

	bool Scene::run() {
		double time = glfwGetTime();

		double deltaTime = time - m_time;
		m_time = time;
		m_renderer->setCamera(m_camera);
		m_renderer->startShader(this->shaderHelper->getProgramId());
		bool won = true;
		do {
			glfwPollEvents();
			m_physicsWorld->runPhysics(deltaTime);
			m_renderer->beginDrawing(this->window);
			
			m_gameObjectManager->update(deltaTime);
			m_gameObjectManager->render(m_renderer);

			m_renderer->endDrawing(this->window);

			for (auto newGameObject : m_extraGameObjectManager->getGameObjects()) {
				m_gameObjectManager->addObject(newGameObject);
			}
			if (!m_extraGameObjectManager->getGameObjects().empty()) {
				m_extraGameObjectManager->getGameObjects().clear();
			}
			

			won = true;
			bool lost = false;
			for (auto enemy : m_enemies) {
				if (!enemy->isDead()) {
					won = false;
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
}