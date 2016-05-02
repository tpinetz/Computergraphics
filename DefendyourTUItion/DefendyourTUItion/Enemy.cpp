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

		m_mass = 1;

		this->initPhysics(position, 
			new btBoxShape(btVector3(1, 1.5, 1)));
	}
	
	
	void Enemy::update(double time) {
		if (!m_dead) {

			GLfloat deltaTime = time;

			btTransform trans;
			getRigidBody()->getMotionState()->getWorldTransform(trans);
			m_position = glm::vec3(trans.getOrigin().getX(),
				trans.getOrigin().getY(),
				trans.getOrigin().getZ());

			glm::vec3 forceVec = glm::normalize(-m_position) * movementSpeed * (GLfloat)time;
			getRigidBody()->setLinearVelocity(btVector3(forceVec.x, forceVec.y, forceVec.z));
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
}
