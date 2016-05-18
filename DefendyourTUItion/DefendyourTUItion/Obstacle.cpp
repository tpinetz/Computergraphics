#include "Obstacle.h"

namespace GameObject {

	Obstacle::Obstacle(std::shared_ptr<ModelLoader> model, GLuint shader)
		:m_model(model),
		m_shader(shader)
	{
		this->m_position = glm::vec3(1.f, 1.f, -1.f);
		this->m_scale = glm::vec3(1.f, 1.f, 11.f);
		
		initPhysics(m_position, new btBoxShape(btVector3(1.f, 1.f, 1.f)));
		this->m_transform = getTransformMatrix();
	}


	Obstacle::~Obstacle()
	{
	}


	void Obstacle::update(double time) {

	}

	void Obstacle::render(std::shared_ptr<Renderer::Renderer> renderer) {
		if (!m_active) {
			return;
		}

		renderer->startShader(m_shader);
		renderer->drawModel(*m_model, m_transform);
		renderer->stopShader();
	}

	void Obstacle::handlePhysicsCollision(PhysicsObject* otherObject) {

	}
}