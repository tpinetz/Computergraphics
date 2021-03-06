#include "Game.h"

namespace Game {


	Game::Game(GLint width, GLint height)
		:m_top(height),
		m_right(width)
	{
	}


	Game::~Game()
	{
		delete Input::KeyboardManager::getKeyboardManager();
		delete Input::MouseInputManager::getMouseInputManagerInstance();
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	bool Game::init() {
		if (!glfwInit()) {
			std::cerr << "Test!";
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


		this->m_window = glfwCreateWindow(m_right, m_top, "Defend your TUItion", NULL, NULL);
		if (this->m_window == NULL) {
			std::cerr << "Failed to create Window";
			return false;
		}
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glViewport(0, 0, m_right, m_top);


		glfwMakeContextCurrent(this->m_window);
		glewExperimental = true;
		if (glewInit() != GLEW_OK) {
			std::cerr << "Failed to initialize.";
			return false;
		}

		glfwSetInputMode(this->m_window, GLFW_STICKY_KEYS, GL_TRUE);
		glEnable(GL_CULL_FACE);     // Cull back facing polygons
		glCullFace(GL_BACK);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);


		return true;
	}

	void Game::run() {
		Scene::Scene* scene = 0;
		int level = 1;
		while (level <= m_maxLevel) {
			scene = new Scene::Scene(m_window, m_right, m_top);
			scene->init("../Assets/level" + std::to_string(level) + ".txt");
			
			if (!scene->runIntro(std::to_string(level))) {
				break;
			}
			bool won = scene->run();
			scene->runOutro(std::to_string(level), won);
			level += won;
			
			if (Input::KeyboardManager::getKeyboardManager()->isKeyPressed(GLFW_KEY_ESCAPE)) break;

			delete scene;
			scene = 0;
		}
		if (scene) {
			delete scene;
		}

	}

}