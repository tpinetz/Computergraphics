#include "Camera.h"


namespace Camera {

	Camera::Camera(Input::KeyboardManager* keyboardManager, float right, float top) 	{
		m_cameraPos = glm::vec3(0.0f, 1.5f, -1.0f);
		m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_cameraSpeed = 0.05f;
		m_mouseSensitivity = 0.4f;

		m_keyboardManager = keyboardManager;
		m_orthoMatrix = glm::ortho(0.0f, right, 0.0f, top, 0.1f, 100.0f);
		m_projMatrix = glm::perspective(45.0f, right / top, 0.1f, 100.0f);

		m_yaw = YAW;
		m_pitch = PITCH;

		updateCameraVectors();
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

	void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset) {
		xoffset *= m_mouseSensitivity;
		yoffset *= m_mouseSensitivity;

		m_yaw += xoffset;
		m_pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (this->m_pitch > 89.0f)
			this->m_pitch = 89.0f;
		if (this->m_pitch < -89.0f)
			this->m_pitch = -89.0f;

		updateCameraVectors();
	}

	void Camera::updateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		front.y = sin(glm::radians(m_pitch));
		front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
		m_cameraFront = glm::normalize(front);
		glm::vec3 camRight = glm::normalize(glm::cross(m_cameraFront, m_worldUp));

		m_cameraUp = glm::normalize(glm::cross(camRight, m_cameraFront));
	}
}