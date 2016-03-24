#include "Camera.h"


namespace Camera {

	Camera::Camera(std::shared_ptr<Input::KeyboardManager> keyboardManager) 	{
		m_cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_cameraSpeed = 0.05f;

		m_keyboardManager = keyboardManager;
	}


	Camera::~Camera()
	{
	}

	void Camera::update(float deltaTime) {
		
		if (m_keyboardManager->isKeyPressed(GLFW_KEY_W)) {
			m_cameraPos += m_cameraSpeed * m_cameraFront * deltaTime;
		}

		if (m_keyboardManager->isKeyPressed(GLFW_KEY_S)) {
			m_cameraPos -= m_cameraSpeed * m_cameraFront * deltaTime;
		}

		if (m_keyboardManager->isKeyPressed(GLFW_KEY_A)) {
			m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed * deltaTime;
		}

		if (m_keyboardManager->isKeyPressed(GLFW_KEY_D)) {
			m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed * deltaTime;
		}
	}
}