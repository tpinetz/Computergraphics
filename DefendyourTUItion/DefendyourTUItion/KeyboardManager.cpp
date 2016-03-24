#include "KeyboardManager.h"

namespace Input {

	KeyboardManager* KeyboardManager::m_instance = NULL;

	KeyboardManager::KeyboardManager()
	{
		for (int i = 0; i < m_NUM_KEYS; i++) {
			m_keys[i] = false;
		}
	}


	KeyboardManager::~KeyboardManager()
	{
	}

	KeyboardManager* KeyboardManager::getKeyboardManager() {
		if (m_instance == NULL) {
			m_instance = new KeyboardManager();
		}
		return m_instance;
	}

	void KeyboardManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		KeyboardManager::getKeyboardManager()->member_key_callback(key, action);
	}


	void KeyboardManager::member_key_callback(int key, int action) {
		if (action == GLFW_PRESS) {
			m_keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			m_keys[key] = false;
		}
	}

	bool KeyboardManager::isKeyPressed(int key) {
		return m_keys[key];
	}

}
