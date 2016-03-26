#pragma once
#include "MainHeaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "KeyboardManager.h"

namespace Camera {

	class Camera
	{
	public:
		Camera(std::shared_ptr<Input::KeyboardManager> keyboardManager, float right, float top);
		~Camera();

		void update(float deltaTime);
		inline glm::vec3 getCameraPosition() {
			return m_cameraPos;
		}
		inline glm::mat4 getViewMatrix() {
			return m_viewMatrix;
		}

		inline glm::mat4 getProjectionMatrix() {
			return m_projMatrix;
		}
	private:
		glm::vec3 m_cameraPos; 
		glm::vec3 m_cameraFront;
		
		glm::vec3 m_cameraUp;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_orthoMatrix;
		glm::mat4 m_projMatrix;
		GLfloat m_cameraSpeed;

		std::shared_ptr<Input::KeyboardManager> m_keyboardManager;
	};


}