#include "Camera.h"


namespace Camera {

	Camera::Camera(std::shared_ptr<Input::KeyboardManager> keyboardManager, float right, float top) 	{
		m_cameraPos = glm::vec3(0.0f, 0.0f, -3.0f);
		m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_cameraSpeed = 50.f;

		m_keyboardManager = keyboardManager;
		m_orthoMatrix = glm::ortho(0.0f, right, 0.0f, top, 0.1f, 100.0f);
		m_projMatrix = glm::perspective(45.0f, right / top, 0.1f, 100.0f);
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

		/*m_viewMatrix = glm::lookAt(m_cameraPos,
			m_cameraPos + m_cameraUp,
			m_cameraUp); */
		glm::mat4 view;
		m_viewMatrix = glm::translate(view, m_cameraPos);
	}
}