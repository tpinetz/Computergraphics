#pragma once
#include "MainHeaders.h"
#include "Scene.h"
#include "MouseInputManager.h"
#include "KeyboardManager.h"
#include "glm\glm.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H

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
		FT_Library  library;
		GLint m_top;
		GLint m_right;
		int m_maxLevel = 2;
	};
}

