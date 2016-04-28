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

		this->initPhysics(position);
	}

	void Enemy::initPhysics(glm::vec3 position) {
		m_shape = std::shared_ptr<btCollisionShape>(new btSphereShape(1));
		m_motionState = std::shared_ptr<btDefaultMotionState>(
			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), 
			btVector3(position.x,position.y, position.z)))
			);

		m_fallInertia = btVector3(0, 0, 0);
		m_shape->calculateLocalInertia(m_mass, m_fallInertia);
		

		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
			m_mass, 
			m_motionState.get(), 
			m_shape.get(), 
			m_fallInertia);
		m_rigidBody = std::shared_ptr<btRigidBody>(new btRigidBody(rigidBodyCI));

	}


	
	void Enemy::update(double time) {
		GLfloat deltaTime = time;

		btTransform trans;
		m_rigidBody->getMotionState()->getWorldTransform(trans);
		m_position.y = trans.getOrigin().getY();


		m_position += glm::normalize(-m_position) * movementSpeed * deltaTime;

	}


	void Enemy::render(std::shared_ptr<Renderer::Renderer> renderer) {

		glm::mat4 transform = getTransformMatrix();
		renderer->startShader(m_shader);
		renderer->drawModel(mod, transform);
		renderer->stopShader();
	}
}
