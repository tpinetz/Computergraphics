#pragma once
#include "MainHeaders.h"
#include "glm\glm.hpp"
#include "KeyboardManager.h"

namespace Camera {

	class Camera
	{
	public:
		Camera(std::shared_ptr<Input::KeyboardManager> keyboardManager);
		~Camera();

		void update(float deltaTime);

	private:
		glm::vec3 m_cameraPos; 
		glm::vec3 m_cameraFront;
		
		glm::vec3 m_cameraUp;
		GLfloat m_cameraSpeed;

		std::shared_ptr<Input::KeyboardManager> m_keyboardManager;
	};


}