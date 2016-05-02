#include "Podest.h"

namespace GameObject {

	Podest::Podest(GLuint shader, std::shared_ptr<Renderer::Model> model)
		:m_shader(shader),
		m_model(model)
	{
		m_position = glm::vec3(0, 0, 0);
		m_scale = glm::vec3(0.5, 1, 0.5);
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
}
