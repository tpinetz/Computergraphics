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

	void Podest::render(std::shared_ptr<Renderer::Renderer> renderer) {
		m_frustum->updateFrustum(m_transform);

		if (m_frustum->pointInFrustum(0.0f, 0.0f, 0.0f)) {
			std::cout << "Point is in Frustum" << std::endl;
		}
		else {
			std::cout << "Point not in Frustum" << std::endl;
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
	}

	void Podest::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		renderer->startShader(shader);
		renderer->drawShadow(m_model, m_transform);
		renderer->stopShader();
	}
}
