#include "Scene.h"

namespace Scene {

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};



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

		glfwMakeContextCurrent(this->window);
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to initialize.";
			return false;
		}

		glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);

		// It is important that the Physics is initialized first.
		return initPhysics() && initInternalObjects() && addSceneRelevantGameObjects();
	}

	bool Scene::initPhysics() {
		m_physicsWorld = std::shared_ptr<Physics::PhysicsWorld>(new Physics::PhysicsWorld());

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

		
		auto ground = std::shared_ptr<GameObject::Ground>(new GameObject::Ground(m_textureShader->getProgramId(), 1000, 1000));
		m_gameObjectManager->addObject(ground);
		m_physicsWorld->addPhysicsObject(ground);

		
		auto enemy1 = std::shared_ptr<GameObject::Enemy>(
			new GameObject::Enemy("enemy1", glm::vec3(1, 3, -10), 
			m_textureShader->getProgramId()));
		m_gameObjectManager->addObject(enemy1);
		m_physicsWorld->addPhysicsObject(enemy1);
		m_enemies.push_back(enemy1);

		auto enemy2 = std::shared_ptr<GameObject::Enemy>(
			new GameObject::Enemy("enemy2", glm::vec3(5, 1, -13),
			m_textureShader->getProgramId()));
		m_gameObjectManager->addObject(enemy2);
		m_physicsWorld->addPhysicsObject(enemy2);
		m_enemies.push_back(enemy2);

		std::shared_ptr<GameObject::Light> light = std::shared_ptr<GameObject::Light>(
			new GameObject::Light(
			glm::vec3(1.0f,1.0f,1.0f),      // Position
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
		
		m_renderer->stopShader();

		return true;
	}
}