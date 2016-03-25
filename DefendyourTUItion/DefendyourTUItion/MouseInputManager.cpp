#include "MouseInputManager.h"

namespace Input {
	MouseInputManager* MouseInputManager::m_instance = NULL;


	MouseInputManager::MouseInputManager()
	{
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

}