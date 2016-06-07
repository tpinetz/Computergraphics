#include "Obstacle.h"

namespace GameObject {

	Obstacle::Obstacle(std::shared_ptr<ModelLoader> model, GLuint shader, glm::vec3 position, glm::vec3 scale)
		:m_model(model),
		m_shader(shader)
	{
		this->m_position = position;
		this->m_scale = scale;
		
		initPhysics(m_position, new btBoxShape(btVector3(2.0f, 2.0f, 2.0f)));
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

	void Obstacle::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		if (!m_active) {
			return;
		}

		renderer->startShader(shader);
		renderer->drawShadow(*m_model, m_transform);
		renderer->stopShader();
	}


	void Obstacle::handlePhysicsCollision(PhysicsObject* otherObject) {

	}
}