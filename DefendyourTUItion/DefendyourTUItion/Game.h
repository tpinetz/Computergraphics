#pragma once
#include "MainHeaders.h"
#include "Scene.h"
#include "MouseInputManager.h"
#include "KeyboardManager.h"
#include "glm\glm.hpp"

namespace Game {

	class Game
	{
	public:
		Game(GLint width, GLint height);
		~Game();

		bool init();
		void run();

	private:
		GLFWwindow* m_window;
		GLint m_top;
		GLint m_right;
		int m_maxLevel = 3;
	};
}

