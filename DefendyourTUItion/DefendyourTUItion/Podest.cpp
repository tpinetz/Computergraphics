#include "Podest.h"

namespace GameObject {

	Podest::Podest(GLuint shader, std::shared_ptr<Renderer::Model> model)
		:m_shader(shader),
		m_model(model)
	{
		m_position = glm::vec3(2.0f, 0.0f, 1.0);
		m_scale = glm::vec3(1, 2, 1);
		m_transform = getTransformMatrix();
	}


	Podest::~Podest()
	{
	}

	void Podest::update(double time) {

	}

	void Podest::render(std::shared_ptr<Renderer::Renderer> renderer) {
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
	}

	void Podest::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		renderer->startShader(shader);
		renderer->drawShadow(m_model, m_transform);
		renderer->stopShader();
	}
}
