#include "Scene.h"

namespace Scene {

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};



	Scene::Scene()
	{
		m_keyboardManager = std::shared_ptr<Input::KeyboardManager>(Input::KeyboardManager::getKeyboardManager());
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


		this->window = glfwCreateWindow(1024, 768, "Defend your TUItion", NULL, NULL);
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
		if (!this->shaderHelper->loadShader("VertexShader.vertexshader", "fragmentShader.fragmentshader")) {
			std::cerr << "Failed to read Shader";
			return false;
		}


		return initBullet() && initInternalObjects();
	}

	bool Scene::initBullet() {
		m_btBroadphaseInterface = std::shared_ptr<btBroadphaseInterface>(new btDbvtBroadphase());


		return true;
	}

	bool Scene::initInternalObjects() {
		m_gameObjectManager = std::shared_ptr<GameObjectManager::GameObjectManager>(new GameObjectManager::GameObjectManager());
		std::shared_ptr<Camera::Camera> camera = std::shared_ptr<Camera::Camera>(
			new Camera::Camera(m_keyboardManager));
		
		m_gameObjectManager->addObject(
			std::shared_ptr<GameObject::GameObject>(
				new Avatar::Avatar(camera)));
		m_time = glfwGetTime();

		glfwSetKeyCallback(window, Input::KeyboardManager::key_callback);

		return true;
	}

	bool Scene::run() {
		glGenBuffers(1, &this->vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		double time = glfwGetTime();

		double deltaTime = time - m_time;
		m_time = time;

		do {
			this->render();
			
			m_gameObjectManager->update(deltaTime);
			m_gameObjectManager->render();
		} while (!m_keyboardManager->isKeyPressed(GLFW_KEY_ESCAPE) &&
			glfwWindowShouldClose(this->window) == 0);

		return true;
	}

	void Scene::render() {
		glfwSwapBuffers(this->window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(this->shaderHelper->getProgramId());

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, this->vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
		glDisableVertexAttribArray(0);
	}

}