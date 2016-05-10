#include "Scene.h"

namespace Scene {

	Scene::Scene()
		:Scene(1024, 768)
	{
	}

	Scene::Scene(float right, float top) {
		m_right = right;
		m_top = top;
	}


	Scene::~Scene()
	{
		glUseProgram(0);
		glfwTerminate();
	}


	bool Scene::init() {
		if (!glfwInit()) {
			std::cerr << "Test!";
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


		this->window = glfwCreateWindow(m_right, m_top, "Defend your TUItion", NULL, NULL);
		if (this->window == NULL) {
			std::cerr << "Failed to create Window";
			return false;
		}
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		

		glfwMakeContextCurrent(this->window);
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to initialize.";
			return false;
		}

		glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);

		
		glEnable(GL_CULL_FACE);     // Cull back facing polygons
		glCullFace(GL_BACK);

		// It is important that the Physics is initialized first.
		return initPhysics() && initInternalObjects() && addSceneRelevantGameObjects();
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

		m_keyboardManager = std::shared_ptr<Input::KeyboardManager>(Input::KeyboardManager::getKeyboardManager());
		m_mouseInputManager = std::shared_ptr<Input::MouseInputManager>
			(Input::MouseInputManager::getMouseInputManagerInstance());

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

		ModelLoader mod;
		mod.loadModel("../Assets/Model/nanosuit/nanosuit.obj");
		
		auto enemy1 = std::shared_ptr<GameObject::Enemy>(
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
		m_enemies.push_back(enemy5);

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

	bool Scene::run() {
		double time = glfwGetTime();

		double deltaTime = time - m_time;
		m_time = time;
		m_renderer->setCamera(m_camera);
		m_renderer->startShader(this->shaderHelper->getProgramId());

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
			

			bool won = true;
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
		glfwDestroyWindow(window);
		delete m_physicsWorld;

		return true;
	}
}