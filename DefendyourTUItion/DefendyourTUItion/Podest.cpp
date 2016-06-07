#include "Podest.h"

namespace GameObject {

	Podest::Podest(GLuint shader, std::shared_ptr<Renderer::Model> model)
		:m_shader(shader),
		m_model(model)
	{
		m_position = glm::vec3(2.0f, 1.0f, 1.0);
		m_scale = glm::vec3(1, 2, 1);
		m_transform = getTransformMatrix();
	}


	Podest::~Podest()
	{
	}

	void Podest::update(double time) {

	}

	void Podest::render(std::shared_ptr<Renderer::Renderer> renderer) {
		renderer->startShader(m_shader);
		renderer->drawModel(m_model, m_transform);
		renderer->stopShader();
	}

	void Podest::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
	//	renderer->startShader(shader);
	//	renderer->drawShadow(m_model, m_transform);
	//	renderer->stopShader();
	}
}
