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
#include "Podest.h"
#include "DirectionalLight.h"
#include "SkyBox.h"
#include "Obstacle.h"

namespace Scene {

	class Scene
	{
	private:
		bool initInternalObjects();
		bool addSceneRelevantGameObjects();
		bool initPhysics();
		bool addLevelDependantObjects(std::string levelFileName);

	public:
		Scene(GLFWwindow* window, float right, float top);
		~Scene();

		bool init(std::string levelFileName);

		bool run();

	private:
		GLFWwindow* window;
		std::shared_ptr<ShaderHelper> shaderHelper;
		std::shared_ptr<ShaderHelper> m_textureShader;
		std::shared_ptr<ShaderHelper> m_meshShader;
		// Used to store current Game Objects while the game is running
		std::shared_ptr<GameObjectManager::GameObjectManager> m_gameObjectManager;
		// Used to allocate new Game Objects while the game is running
		std::shared_ptr<GameObjectManager::GameObjectManager> m_extraGameObjectManager; 

		// Current Time
		double m_time;
		float m_top;
		float m_right;
		
		// Input Handler Objects
		Input::KeyboardManager* m_keyboardManager;
		Input::MouseInputManager* m_mouseInputManager;
		std::shared_ptr<Renderer::Renderer> m_renderer;
		std::shared_ptr<Camera::Camera> m_camera;
		std::shared_ptr<GameObject::DirectionalLight> m_sun;
		
		// Bullet World
		Physics::PhysicsWorld* m_physicsWorld;
		vector < std::shared_ptr<GameObject::Enemy>> m_enemies;

		ModelLoader mod;
	};

}