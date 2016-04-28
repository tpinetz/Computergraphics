#include "Avatar.h"

namespace GameObject{

	Avatar::Avatar(std::shared_ptr<Camera::Camera> camera, GLuint shader, 
		std::shared_ptr<GameObjectManager::GameObjectManager> gameObjectManager, GLuint projectileShader)
	{
		m_name = "Avatar";
		m_camera = camera;
		m_position = m_camera->getCameraPosition();
		m_scale = glm::vec3(0.0f, 0.0f, 0.0f);
		m_gameObjectManager = gameObjectManager;

		m_shader = shader;
		m_projectileShader = projectileShader;

		initModel();
	}

	void Avatar::initModel() {

	}


	Avatar::~Avatar()
	{
	}

	void Avatar::update(double deltaTime) {
		m_position = m_camera->getCameraPosition();
		m_bulletCooldown -= deltaTime;
		if (Input::MouseInputManager::getMouseInputManagerInstance()
			->isKeyPressed(GLFW_MOUSE_BUTTON_1) && m_bulletCooldown < 0.0f) {
			std::shared_ptr<Projectile> newProjectile =
				std::shared_ptr<Projectile>(new Projectile(m_projectileShader, m_position, glm::vec3(0.2f, 0.2f, 0.2f), m_camera->getCameraDirection()));
			m_gameObjectManager->addObject(newProjectile);
			m_bulletCooldown = m_bulletCooldownAttribute;
		}
	}

	void Avatar::render(std::shared_ptr<Renderer::Renderer> renderer) {

	}
}