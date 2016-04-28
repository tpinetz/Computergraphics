#pragma once
#include "MainHeaders.h"	
#include "Camera.h"

namespace Input {

	class MouseInputManager
	{
	private:
		MouseInputManager();
		void memberCallback(int button, int action);

	public:
		~MouseInputManager();
		static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

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

		bool m_keys[100];
		int m_numKeys = 100;
	};

}