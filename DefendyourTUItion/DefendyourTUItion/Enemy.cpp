#include "Enemy.h"

namespace GameObject {
	std::string Enemy::m_typeName = "Enemy";

	Enemy::~Enemy()
	{
	}

	Enemy::Enemy(std::string name, glm::vec3 position, GLuint shader, ModelLoader& mod)
	{
		this->m_name = m_typeName;
		this->m_position = position;
		this->m_scale = glm::vec3(0.2f, 0.2f, 0.2f);
		this->m_shader = shader;
		this->mod = mod;

		m_mass = 10;
		this->initPhysics(position, 
			new btBoxShape(btVector3(1.5, 2, 1)));
	}
	
	
	void Enemy::update(double time) {
		if (!m_dead) {
			btTransform trans = getRigidBody()->getCenterOfMassTransform();
			m_position = glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
			//std::cout << "Enemy game position: " << Common::FormattingHelper::getFormattedVectorString(m_position) << std::endl;

			glm::vec3 forceVec = glm::normalize(-m_position) * movementSpeed *  (GLfloat)time;
			m_position += forceVec;
			setPhysicsPosition(m_position);
			//std::cout << "Enemy Position after updating: (" << trans.getOrigin().getX() << "," << trans.getOrigin().getY() << "," << trans.getOrigin().getZ() << ")" << std::endl;
		}
	}

	void Enemy::handlePhysicsCollision(PhysicsObject* otherObject) {
		m_dead = true;
	}


	void Enemy::render(std::shared_ptr<Renderer::Renderer> renderer) {
		if (!m_dead) {
			glm::mat4 transform = getTransformMatrix();
			renderer->startShader(m_shader);
			renderer->drawModel(mod, transform);
			renderer->stopShader();
		}
	}

	void Enemy::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		if (!m_dead) {
			glm::mat4 transform = getTransformMatrix();
			renderer->startShader(shader);
			renderer->drawShadow(mod, transform);
			renderer->stopShader();
		}
	}
}
