#include "Podest.h"

namespace GameObject {

	Podest::Podest(GLuint shader, std::shared_ptr<Renderer::Model> model, std::shared_ptr<Renderer::Frustum> frustum)
		:m_shader(shader),
		m_model(model),
		m_frustum(frustum)
	{
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_scale = glm::vec3(1, 2, 1);
		m_transform = getTransformMatrix();
	}


	Podest::~Podest()
	{
	}

	void Podest::update(double time) {

	}

	int Podest::render(std::shared_ptr<Renderer::Renderer> renderer) {
		m_frustum->updateFrustum(m_transform);

		if (!m_frustum->CubeInFrustum(m_position.x, m_position.y, m_position.z, 4.0f)) {
			return 0;
		}
	
		if (m_alpha < 1.0f) {
			glDisable(GL_CULL_FACE);
		}
		renderer->setAlpha(m_alpha);
		renderer->startShader(m_shader);
		renderer->drawModel(m_model, m_transform);
		renderer->stopShader();
		renderer->setAlpha(1.0f);

		if (m_alpha < 1.0f) {
			glEnable(GL_CULL_FACE);
		}
		return 1;
	}

	void Podest::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		renderer->startShader(shader);
		renderer->drawShadow(m_model, m_transform);
		renderer->stopShader();
	}
}
