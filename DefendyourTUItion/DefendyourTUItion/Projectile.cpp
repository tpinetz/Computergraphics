#include "Projectile.h"

namespace GameObject{

	Projectile::Projectile()
	{
	}

	Projectile::Projectile(GLuint shader, glm::vec3 position, 
		glm::vec3 scale, glm::vec3 direction, std::shared_ptr<Renderer::Model> model) {
		this->m_position = position;
		this->m_scale = scale;
		this->m_direction = direction;
		this->m_shader = shader;
		this->m_model = model;


		initPhysics(m_position, std::shared_ptr<btCollisionShape>(new btBoxShape(btVector3(1, 1, 1))));

		glm::vec3 forceVector = m_direction * m_force;
		getRigidBody()->applyCentralForce(btVector3(forceVector.x, forceVector.y, forceVector.z));
	}

	Projectile::~Projectile()
	{
	}


	void Projectile::update(double time) {
		m_lifeTime -= time;
		if (m_active) {
			
			btTransform trans;
			getRigidBody()->getMotionState()->getWorldTransform(trans);
			m_position = glm::vec3(trans.getOrigin().getX(), 
				trans.getOrigin().getY(), 
				trans.getOrigin().getZ());

			if (m_lifeTime <= 0) {
				m_active = false;
			}
		}
	}

	void Projectile::render(std::shared_ptr<Renderer::Renderer> renderer) {
		if (m_active) {
			glm::mat4 transform = getTransformMatrix();
			renderer->startShader(m_shader);

			renderer->drawModel(this->m_model, transform);
			
			renderer->stopShader();
		}
	}
}
