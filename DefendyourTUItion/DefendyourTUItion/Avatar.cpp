#include "Avatar.h"

namespace GameObject{

	Avatar::Avatar(std::shared_ptr<Camera::Camera> camera, 
		Physics::PhysicsWorld* physicsWorld,
		std::shared_ptr<GameObjectManager::GameObjectManager> gameObjectManager, GLuint projectileShader,
		std::shared_ptr<ModelLoader> particleModel, GLuint particleShader)
	{
		m_name = "Avatar";
		m_camera = camera;
		m_position = m_camera->getCameraPosition();
		m_scale = glm::vec3(0.0f, 0.0f, 0.0f);
		m_gameObjectManager = gameObjectManager;
		m_particleModel = particleModel;
		m_particleShader = particleShader;

		m_physicsWorld = physicsWorld;
		m_projectileShader = projectileShader;

		m_projectileModel = Common::ModelLoaderHelper::getInstance()
			->getTextureModel(m_projectileModelString, m_projectileColorString,
			m_projectileTextureString,
			m_projectileSpecTextureString);

		this->initPhysics(m_position,
			new btBoxShape(btVector3(1, 1.5, 1)));
	}


	Avatar::~Avatar()
	{
	}


	void Avatar::handlePhysicsCollision(PhysicsObject* physicsObject) {

	}

	void Avatar::update(double deltaTime) {
		btTransform trans;
		getRigidBody()->getMotionState()->getWorldTransform(trans);
		m_position.y = trans.getOrigin().getY();

		m_camera->setCameraPosition(m_position);
		m_camera->update(deltaTime);
		m_position = m_camera->getCameraPosition();

		m_bulletCooldown -= deltaTime;
		if (Input::MouseInputManager::getMouseInputManagerInstance()
			->isKeyPressed(GLFW_MOUSE_BUTTON_1) && m_bulletCooldown < 0.0f) {
			std::shared_ptr<Projectile> newProjectile =
				std::shared_ptr<Projectile>(new Projectile(m_projectileShader, m_camera->getCameraPosition(), 
				glm::vec3(0.4f, 0.4f, 0.4f), m_camera->getCameraDirection(),
				m_projectileModel, m_camera, m_particleModel, m_particleShader));
			m_gameObjectManager->addObject(newProjectile);
			m_physicsWorld->addPhysicsObject(newProjectile);
			m_bulletCooldown = m_bulletCooldownAttribute;
		}
	}

	void Avatar::render(std::shared_ptr<Renderer::Renderer> renderer) {

	}

	void Avatar::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {

	}
}