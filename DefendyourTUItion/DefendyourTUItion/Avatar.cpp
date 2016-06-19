#include "Avatar.h"

namespace GameObject{

	Avatar::Avatar(std::shared_ptr<Camera::Camera> camera, 
		Physics::PhysicsWorld* physicsWorld,
		std::shared_ptr<GameObjectManager::GameObjectManager> gameObjectManager, GLuint projectileShader,
		std::shared_ptr<ModelLoader> particleModel, GLuint particleShader, std::shared_ptr<Renderer::Frustum> frustum, std::shared_ptr<Ground> ground)
	{
		m_name = "Avatar";
		m_camera = camera;
		m_position = m_camera->getCameraPosition();
		m_position.y = ground->getheightOnCoordinates(m_position.x, m_position.z) + 2.0f;
		m_scale = glm::vec3(0.0f, 0.0f, 0.0f);
		m_gameObjectManager = gameObjectManager;
		m_particleModel = particleModel;
		m_particleShader = particleShader;
		m_ground = ground;

		m_physicsWorld = physicsWorld;
		m_projectileShader = projectileShader;

		m_projectileModel = Common::ModelLoaderHelper::getInstance()
			->getTextureModel(m_projectileModelString, m_projectileColorString,
			m_projectileTextureString,
			m_projectileSpecTextureString);
		m_frustum = frustum;
	}


	Avatar::~Avatar()
	{
	}


	void Avatar::handlePhysicsCollision(PhysicsObject* physicsObject) {

	}

	void Avatar::update(double deltaTime) {
		//btTransform trans = getRigidBody()->getWorldTransform();
		//m_position = glm::vec3(trans.getOrigin().x(), trans.getOrigin().y() + 1.5f, trans.getOrigin().z());
		if (m_startDelay >= 0.0f) {
			m_startDelay -= deltaTime;
		}
		glm::vec3 temp = m_camera->getDirectionVec();
		glm::vec3 force = temp * (float)deltaTime * m_movementspeed;
		m_position += force;
		GLfloat groundHeight = m_ground->getheightOnCoordinates(m_position.x, m_position.z) + 2.0f;
		if (m_jumping) {
			m_currentJumpTime += deltaTime;
			if (m_currentJumpTime > m_jumpTime) {
				m_jumping = false;
			}
			m_position.y += m_jumpAcceleration * deltaTime;
		}
		
		if (m_position.y  < groundHeight - 0.3f) {
			m_position -= force;
		}
		else {
			m_position.y = std::max(groundHeight, m_position.y - m_fallingSpeed * (float) deltaTime);
		}
		
		m_camera->setCameraPosition(m_position);
		

		std::cout << "!Avatar game position: " << Common::FormattingHelper::getFormattedVectorString(m_position) << std::endl;
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
		if (Input::KeyboardManager::getKeyboardManager()->isKeyPressed(GLFW_KEY_SPACE) && !m_jumping && m_startDelay < 0.0f) {
			m_jumping = true;
			m_currentJumpTime = 0.0f;
		}
	}

	int Avatar::render(std::shared_ptr<Renderer::Renderer> renderer) {
		return 0;
	}

	void Avatar::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {

	}
}