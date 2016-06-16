#include "Avatar.h"

namespace GameObject{

	Avatar::Avatar(std::shared_ptr<Camera::Camera> camera, 
		Physics::PhysicsWorld* physicsWorld,
		std::shared_ptr<GameObjectManager::GameObjectManager> gameObjectManager, GLuint projectileShader,
		std::shared_ptr<ModelLoader> particleModel, GLuint particleShader, std::shared_ptr<Renderer::Frustum> frustum)
	{
		m_name = "Avatar";
		m_camera = camera;
		m_position = m_camera->getCameraPosition();
		m_scale = glm::vec3(0.0f, 0.0f, 0.0f);
		m_mass = 10.0f;
		m_gameObjectManager = gameObjectManager;
		m_particleModel = particleModel;
		m_particleShader = particleShader;

		m_physicsWorld = physicsWorld;
		m_projectileShader = projectileShader;

		m_projectileModel = Common::ModelLoaderHelper::getInstance()
			->getTextureModel(m_projectileModelString, m_projectileColorString,
			m_projectileTextureString,
			m_projectileSpecTextureString);
		m_frustum = frustum;

		this->initPhysics(m_position,
			new btBoxShape(btVector3(1, 1, 1)));
	}


	Avatar::~Avatar()
	{
	}


	void Avatar::handlePhysicsCollision(PhysicsObject* physicsObject) {

	}

	void Avatar::update(double deltaTime) {
		btTransform trans = getRigidBody()->getWorldTransform();
		m_position = glm::vec3(trans.getOrigin().x(), trans.getOrigin().y() + 1.5f, trans.getOrigin().z());
		m_camera->setCameraPosition(m_position);

		glm::vec3 temp = m_camera->getDirectionVec();
		btVector3 force = btVector3(temp.x, temp.y, temp.z);
		getRigidBody()->setLinearVelocity(10.0f * force);
		//std::cout << "!Avatar game position: " << Common::FormattingHelper::getFormattedVectorString(m_position) << std::endl;
		//std::cout << "Avatar Position after updating: (" << trans.getOrigin().getX() << "," << trans.getOrigin().getY() << "," << trans.getOrigin().getZ() << ")" << std::endl;

		m_bulletCooldown -= deltaTime;
		if (Input::MouseInputManager::getMouseInputManagerInstance()
			->isKeyPressed(GLFW_MOUSE_BUTTON_1) && m_bulletCooldown < 0.0f) {
			std::shared_ptr<Projectile> newProjectile =
				std::shared_ptr<Projectile>(new Projectile(m_projectileShader, m_camera->getCameraPosition(), 
				glm::vec3(0.4f, 0.4f, 0.4f), m_camera->getCameraDirection(),
				m_projectileModel, m_particleModel, m_particleShader, m_frustum));
			m_gameObjectManager->addObject(newProjectile);
			m_physicsWorld->addPhysicsObject(newProjectile);
			m_bulletCooldown = m_bulletCooldownAttribute;
		}
		if (Input::KeyboardManager::getKeyboardManager()->isKeyPressed(GLFW_KEY_SPACE)) {
			
		}
	}

	int Avatar::render(std::shared_ptr<Renderer::Renderer> renderer) {
		return 0;
	}

	void Avatar::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {

	}
}