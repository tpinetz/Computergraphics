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
#include "Light.h"
#include "Enemy.h"
#include "Ground.h"

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
		std::shared_ptr<ShaderHelper> shaderHelper;
		std::shared_ptr<ShaderHelper> m_textureShader;
		// Used to store current Game Objects while the game is running
		std::shared_ptr<GameObjectManager::GameObjectManager> m_gameObjectManager;
		// Used to allocate new Game Objects while the game is running
		std::shared_ptr<GameObjectManager::GameObjectManager> m_extraGameObjectManager; 

		// Current Time
		double m_time;
		float m_top;
		float m_right;
		
		// Input Handler Objects
		std::shared_ptr<Input::KeyboardManager> m_keyboardManager;
		std::shared_ptr<Input::MouseInputManager> m_mouseInputManager;
		std::shared_ptr<Renderer::Renderer> m_renderer;
		std::shared_ptr<Camera::Camera> m_camera;
		
		// Bullet World
		std::shared_ptr<Physics::PhysicsWorld> m_physicsWorld;

	};

}