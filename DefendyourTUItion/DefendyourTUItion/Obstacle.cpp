#include "Obstacle.h"

namespace GameObject {

	Obstacle::Obstacle(std::shared_ptr<ModelLoader> model, GLuint shader, glm::vec3 position, glm::vec3 scale,
		std::shared_ptr<Renderer::Frustum> frustum)
		:m_model(model),
		m_shader(shader),
		m_frustum(frustum)
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

	int Obstacle::render(std::shared_ptr<Renderer::Renderer> renderer) {
		m_frustum->updateFrustum(m_transform);
		if (!m_active || !m_frustum->CubeInFrustum(0.0f, 0.0f,0.0f , 5.0f)) {
			return 0;
		}

		renderer->startShader(m_shader);
		renderer->drawModel(*m_model, m_transform);
		renderer->stopShader();

		return 1;
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