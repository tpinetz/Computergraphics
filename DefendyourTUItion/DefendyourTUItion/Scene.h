#pragma once
#include "MainHeaders.h"
#include "GameObjectManager.h"
#include "ShaderHelper.h"
#include <direct.h>
#include "Avatar.h"
#include "KeyboardManager.h"
#include "btBulletDynamicsCommon.h"
#include "Renderer.h"

namespace Scene {

	class Scene
	{
	private:
		void render();
		bool initInternalObjects();
		bool initBullet();

	public:
		Scene();
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
		std::shared_ptr<Input::KeyboardManager> m_keyboardManager;
		std::shared_ptr<btBroadphaseInterface> m_btBroadphaseInterface;
		std::shared_ptr<Renderer::Renderer> m_renderer;

	};

}