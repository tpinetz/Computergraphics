#pragma once
#include "MainHeaders.h"
#include "GameObjectManager.h"
#include "ShaderHelper.h"
#include <direct.h>
#include "Avatar.h"
#include "KeyboardManager.h"
#include "MouseInputManager.h"
#include "Renderer.h"
#include "Scene.h"
#include "Floor.h"
#include "PhysicsWorld.h"

namespace Scene {

	class Scene
	{
	private:
		bool initInternalObjects();
		bool addSceneRelevantGameObjects();

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
		std::shared_ptr<Renderer::Renderer> m_renderer;
		std::shared_ptr<Camera::Camera> m_camera;
		std::shared_ptr<Physics::PhysicsWorld> m_physicsWorld;

	};

}