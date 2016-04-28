#pragma once
#include "MainHeaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "KeyboardManager.h"

namespace Camera {

	const GLfloat YAW = -90.0f;
	const GLfloat PITCH = 0.0f;
	const GLfloat SPEED = 3.0f;
	const GLfloat SENSITIVTY = 0.25f;
	const GLfloat ZOOM = 45.0f;

	class Camera
	{
	private:
		void updateCameraVectors();

	public:
		Camera(std::shared_ptr<Input::KeyboardManager> keyboardManager, float right, float top);
		~Camera();

		void update(float deltaTime);
		void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset);

		inline glm::vec3 getCameraPosition() {
			return m_cameraPos;
		}

		inline void setCameraPosition(glm::vec3 position) {
			m_cameraPos = position;
		}

		inline glm::mat4 getViewMatrix() {
			return glm::lookAt(m_cameraPos,
				m_cameraPos + m_cameraFront,
				m_cameraUp);;
		}

		inline glm::mat4 getProjectionMatrix() {
			return m_projMatrix;
		}

		inline glm::vec3 getCameraDirection() {
			return m_cameraFront;
		}
	private:
		glm::vec3 m_cameraPos; 
		glm::vec3 m_cameraFront;
		
		glm::vec3 m_cameraUp;
		glm::vec3 m_worldUp;
		glm::mat4 m_orthoMatrix;
		glm::mat4 m_projMatrix;
		GLfloat m_cameraSpeed;
		GLfloat m_mouseSensitivity;
		GLfloat m_yaw;
		GLfloat m_pitch;

		std::shared_ptr<Input::KeyboardManager> m_keyboardManager;
	};


}