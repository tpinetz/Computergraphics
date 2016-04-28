#include "MouseInputManager.h"

namespace Input {
	MouseInputManager* MouseInputManager::m_instance = NULL;


	MouseInputManager::MouseInputManager()
	{
		for (int i = 0; i < m_numKeys; i++) {
			m_keys[i] = 0;
		}
	}


	MouseInputManager::~MouseInputManager()
	{
	}

	MouseInputManager* MouseInputManager::getMouseInputManagerInstance() {
		if (m_instance == NULL) {
			m_instance = new MouseInputManager();
		}
		return m_instance;
	}

	void MouseInputManager::setCamera(std::shared_ptr<Camera::Camera> camera) {
		m_camera = camera;
	}

	void MouseInputManager::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
		m_instance->member_key_callback(xpos, ypos);
	}

	void MouseInputManager::member_key_callback(double xpos, double ypos) {
		if (m_firstMouse)
		{
			m_lastX = xpos;
			m_lastY = ypos;
			m_firstMouse = false;
		}

		GLfloat xoffset = xpos - m_lastX;
		GLfloat yoffset = m_lastY - ypos;  // Reversed since y-coordinates go from bottom to left

		m_lastX = xpos;
		m_lastY = ypos;

		if (m_camera != NULL) {
			m_camera->ProcessMouseMovement(xoffset, yoffset);
		}
	}

	void MouseInputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		MouseInputManager::getMouseInputManagerInstance()->memberCallback(button, action);
	}

	void MouseInputManager::memberCallback(int button, int action) {
		if (action == GLFW_PRESS) {
			m_keys[button] = true;
		}
		else if ( action == GLFW_RELEASE) {
			m_keys[button] = false;
		}
	}

	bool MouseInputManager::isKeyPressed(int key) {
		return m_keys[key];
	}

}