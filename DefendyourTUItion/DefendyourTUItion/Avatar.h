#pragma once
#include "PhysicsObject.h"
#include "Camera.h"
#include "Model.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "MouseInputManager.h"
#include "Projectile.h"
#include "ModelLoaderHelper.h"
#include "PhysicsWorld.h"

namespace GameObject {


	class Avatar :
		public PhysicsObject
	{
	public:
		Avatar(std::shared_ptr<Camera::Camera> camera, 
			Physics::PhysicsWorld* physicsWorld,
			std::shared_ptr<GameObjectManager::GameObjectManager> gameObjectManager, GLuint projectileShader, 
			std::shared_ptr<ModelLoader> particleModel, GLuint particleShader);
		~Avatar();
		void update(double deltaTime);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader);

		void handlePhysicsCollision(PhysicsObject* physicsObject);

		bool operator==(const Avatar& rhs) {
			return m_name == rhs.m_name;
		}

		inline bool isActive() {
			return true;
		}

	private:
		std::shared_ptr<Camera::Camera> m_camera;
		std::shared_ptr<Renderer::Model> m_model;
		std::shared_ptr<GameObjectManager::GameObjectManager> m_gameObjectManager;
		Physics::PhysicsWorld* m_physicsWorld;

		std::shared_ptr<Renderer::Model> m_projectileModel;
		std::string m_projectileModelString = "../Assets/Model/Floor/Floor.obj";
		std::string m_projectileColorString = "../Assets/Textures/ground01.jpg";
		std::string m_projectileTextureString = "../Assets/Textures/ground01b.jpg";
		std::string m_projectileSpecTextureString = "../Assets/Textures/ground01s.jpg";

		GLuint m_projectileShader;
		GLuint m_particleShader;

		GLfloat m_bulletCooldownAttribute = .4f; // How long it takes for the weapon to cool down ( e.g. I can fire ever x milliseconds)
		GLfloat m_bulletCooldown = 0.0f; // How long the weapon still cools down;
		std::shared_ptr<ModelLoader> m_particleModel;

	};

}