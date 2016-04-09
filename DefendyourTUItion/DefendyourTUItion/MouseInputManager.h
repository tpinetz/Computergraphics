#pragma once
#include "MainHeaders.h"	
#include "Camera.h"

namespace Input {

	class MouseInputManager
	{
	private:
		MouseInputManager();

	public:
		~MouseInputManager();
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

		static MouseInputManager* getMouseInputManagerInstance();
		bool isKeyPressed(int key);
		void member_key_callback(double xpos, double ypos);
		void setCamera(std::shared_ptr<Camera::Camera> camera);

	private:
		bool m_firstMouse;
		double m_lastX;
		double m_lastY;

		std::shared_ptr<Camera::Camera> m_camera = NULL;
		static MouseInputManager* m_instance;
	};

}