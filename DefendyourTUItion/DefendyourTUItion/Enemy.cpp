#include "Enemy.h"

namespace GameObject {

	Enemy::~Enemy()
	{
	}

	Enemy::Enemy(std::string name, glm::vec3 position, GLuint shader)
	{
		this->m_name = name;
		this->m_position = position;
		this->m_scale = glm::vec3(0.2f, 0.2f, 0.2f);
		this->m_shader = shader;

		mod.loadModel(m_modelString.c_str());
		m_mass = 1;

		this->initPhysics(position, 
			std::shared_ptr<btCollisionShape>(new btBoxShape(btVector3(1, 1.5, 1))));
	}
	
	
	void Enemy::update(double time) {
		GLfloat deltaTime = time;

		btTransform trans;
		getRigidBody()->getMotionState()->getWorldTransform(trans);
		m_position = glm::vec3(trans.getOrigin().getX(),
			trans.getOrigin().getY(),
			trans.getOrigin().getZ());

		glm::vec3 forceVec = glm::normalize(-m_position) * movementSpeed;
		getRigidBody()->setLinearVelocity(btVector3(forceVec.x, forceVec.y, forceVec.z));
	}


	void Enemy::render(std::shared_ptr<Renderer::Renderer> renderer) {

		glm::mat4 transform = getTransformMatrix();
		renderer->startShader(m_shader);
		renderer->drawModel(mod, transform);
		renderer->stopShader();
	}
}
