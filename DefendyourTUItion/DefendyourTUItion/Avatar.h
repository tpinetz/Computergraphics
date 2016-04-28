#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Model.h"
#include "Renderer.h"
#include "GameObjectManager.h"
#include "MouseInputManager.h"
#include "Projectile.h"

namespace GameObject {


	class Avatar :
		public GameObject
	{
	private:
		void initModel();

	public:
		Avatar(std::shared_ptr<Camera::Camera> camera, GLuint shader, 
			std::shared_ptr<GameObjectManager::GameObjectManager> gameObjectManager, GLuint projectileShader);
		~Avatar();
		void update(double deltaTime);
		void render(std::shared_ptr<Renderer::Renderer> renderer);

		bool operator==(const Avatar& rhs) {
			return m_name == rhs.m_name;
		}
	private:
		std::shared_ptr<Camera::Camera> m_camera;
		std::shared_ptr<Renderer::Model> m_model;
		std::shared_ptr<GameObjectManager::GameObjectManager> m_gameObjectManager;
		static GLfloat m_modelVertices[];
		GLuint m_shader;
		GLuint m_projectileShader;

		GLfloat m_bulletCooldownAttribute = 100.0f; // How long it takes for the weapon to cool down ( e.g. I can fire ever x seconds)
		GLfloat m_bulletCooldown = 0.0f; // How long the weapon still cools down;
	};

}