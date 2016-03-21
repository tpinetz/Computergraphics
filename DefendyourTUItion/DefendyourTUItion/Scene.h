#pragma once
#include "MainHeaders.h"
#include "GameObjectManager.h"
#include "ShaderHelper.h"

namespace Scene {

	class Scene
	{
	private:
		void render();
		bool initInternalObjects();

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

	};

}