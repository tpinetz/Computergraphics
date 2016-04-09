#pragma once
#include "MainHeaders.h"

namespace Input {

	class KeyboardManager
	{
	private: 

		KeyboardManager();
	public:
		~KeyboardManager();
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

		static KeyboardManager* getKeyboardManager();
		bool isKeyPressed(int key);
		void member_key_callback(int key, int action);

	private:
		static const int m_NUM_KEYS = 1024;

		bool m_keys[m_NUM_KEYS];
		static KeyboardManager* m_instance;
	};
}