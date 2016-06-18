#include "Box.h"

namespace GameObject {
	Box::Box(std::shared_ptr<ModelLoader> model, GLuint shader, glm::vec3 position, glm::vec3 scale,
		std::shared_ptr<Renderer::Frustum> frustum)
		:m_shader(shader),
		m_frustum(frustum),
		m_model(model)
	{

		m_position = position;
		m_scale = scale;
		m_mass = 100.0f;
		
		m_position.y += m_scale.y / 2;
		this->initPhysics(m_position, new btBoxShape(btVector3(m_scale.x, m_scale.y, m_scale.z)));
	}


	Box::~Box()
	{
	}

	void Box::update(double time) {
		btTransform trans = getRigidBody()->getWorldTransform();
		m_position = glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
		m_transform = getTransformMatrix();
	}

	int Box::render(std::shared_ptr<Renderer::Renderer> renderer) {
		m_frustum->updateFrustum(m_transform);

		if (!m_frustum->CubeInFrustum(0, 0, 0, 1.0f)) {
			return 0;
		}

		renderer->startShader(m_shader);
		renderer->drawModel(*m_model, m_transform);
		renderer->stopShader();

		return 1;
	}

	void Box::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		renderer->startShader(shader);
		renderer->drawShadow(*m_model, m_transform);
		renderer->stopShader();
	}

	void Box::handlePhysicsCollision(PhysicsObject* otherObject) {

	}

}