#pragma once
#include "MainHeaders.h"
#include "GameObjectManager.h"
#include "ShaderHelper.h"
#include <direct.h>
#include "Avatar.h"
#include "KeyboardManager.h"
#include "MouseInputManager.h"
#include "btBulletDynamicsCommon.h"
#include "Renderer.h"

namespace Scene {

	class Scene
	{
	private:
		bool initInternalObjects();
		bool initBullet();

	public:
		Scene();
		Scene(float right, float top);
		~Scene();

		bool init();

		bool run();

	private:
		GLFWwindow* window;
		GLuint VertexArrayID;
		GLuint vertexbuffer;
		ShaderHelper* shaderHelper;
		std::shared_ptr<GameObjectManager::GameObjectManager> m_gameObjectManager;

		double m_time;
		float m_top;
		float m_right;
		std::shared_ptr<Input::KeyboardManager> m_keyboardManager;
		std::shared_ptr<Input::MouseInputManager> m_mouseInputManager;
		std::shared_ptr<btBroadphaseInterface> m_btBroadphaseInterface;
		std::shared_ptr<Renderer::Renderer> m_renderer;
		std::shared_ptr<Camera::Camera> m_camera;

	};

}