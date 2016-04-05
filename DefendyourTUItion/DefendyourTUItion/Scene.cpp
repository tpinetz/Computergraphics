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
		delete shaderHelper;
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

		glGenVertexArrays(1, &this->VertexArrayID);
		glBindVertexArray(this->VertexArrayID);

		glfwSetInputMode(this->window, GLFW_STICKY_KEYS, GL_TRUE);

		this->shaderHelper = new ShaderHelper();
		if (!this->shaderHelper->loadShader("../DefendyourTUItion/VertexShader.vertexshader", "../DefendyourTUItion/fragmentShader.fragmentshader")) {
			std::cerr << "Failed to read Shader";
			return false;
		}


		return initBullet() && initInternalObjects() && addSceneRelevantGameObjects();
	}

	bool Scene::initBullet() {
		m_btBroadphaseInterface = std::shared_ptr<btBroadphaseInterface>(new btDbvtBroadphase());


		return true;
	}

	bool Scene::initInternalObjects() {
		m_keyboardManager = std::shared_ptr<Input::KeyboardManager>(Input::KeyboardManager::getKeyboardManager());
		m_mouseInputManager = std::shared_ptr<Input::MouseInputManager>
			(Input::MouseInputManager::getMouseInputManagerInstance());

		m_gameObjectManager = std::shared_ptr<GameObjectManager::GameObjectManager>(new GameObjectManager::GameObjectManager());
		m_camera = std::shared_ptr<Camera::Camera>(
			new Camera::Camera(m_keyboardManager, m_right, m_top));

		m_mouseInputManager->setCamera(m_camera);
		


		m_time = glfwGetTime();

		glfwSetKeyCallback(window, Input::KeyboardManager::key_callback);
		glfwSetCursorPosCallback(window, Input::MouseInputManager::mouse_callback);

		m_renderer = std::shared_ptr<Renderer::Renderer>(new Renderer::Renderer());

		return true;
	}

	bool Scene::addSceneRelevantGameObjects() {
		m_gameObjectManager->addObject(
			std::shared_ptr<GameObject::GameObject>(
			new Avatar::Avatar(m_camera)));

		m_gameObjectManager->addObject(
			std::shared_ptr<GameObject::GameObject>(new GameObject::Floor()));

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
			m_renderer->beginDrawing(this->window);
			m_camera->update(deltaTime);
			
			m_gameObjectManager->update(deltaTime);
			m_gameObjectManager->render(m_renderer);
		} while (!m_keyboardManager->isKeyPressed(GLFW_KEY_ESCAPE) &&
			glfwWindowShouldClose(this->window) == 0);
		
		m_renderer->stopShader();

		return true;
	}
}