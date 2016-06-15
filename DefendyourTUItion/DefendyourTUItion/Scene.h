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
#include "DynamicModelLoader.h"

namespace Scene {

	class Scene
	{
	private:
		bool initInternalObjects();
		bool addSceneRelevantGameObjects();
		bool addTransparentGameObjects();
		bool initPhysics();
		bool addLevelDependantObjects(std::string levelFileName);
		void changeSettings(float deltaTime); // Handle the F Keys as described by the LVA.
	public:
		Scene(GLFWwindow* window, float right, float top);
		~Scene();

		bool init(std::string levelFileName);

		bool runIntro(std::string level);
		void runOutro(std::string level, bool won);

		bool run();

	private:
		GLFWwindow* window;
		std::shared_ptr<ShaderHelper> shaderHelper;
		std::shared_ptr<ShaderHelper> m_textureShader;
		std::shared_ptr<ShaderHelper> m_skyboxShader;
		std::shared_ptr<ShaderHelper> m_meshShader;
		std::shared_ptr<ShaderHelper> m_particleShader;
		std::shared_ptr<ShaderHelper> m_textShader;
		std::shared_ptr<ShaderHelper> m_shadowShader;
		std::shared_ptr<ShaderHelper> m_depthTestShader;
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
		std::shared_ptr<GameObject::Avatar> m_avatar;
		std::shared_ptr<GameObject::Podest> m_podest;
		
		// Bullet World
		Physics::PhysicsWorld* m_physicsWorld;
		vector < std::shared_ptr<GameObject::Enemy>> m_enemies;

		// View Frustum Culling
		std::shared_ptr<Renderer::Frustum> m_frustum;

		DynamicModelLoader mod;
		std::shared_ptr<ModelLoader> m_rockModel;

		bool frameTime = false;
		bool wireframeMode = false;
		bool transparentMode = false;
		bool gravityMode = true;
	};

}