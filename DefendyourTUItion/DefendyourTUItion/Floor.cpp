#include "Floor.h"

namespace GameObject {

	Floor::Floor(GLuint shader, GLfloat width, GLfloat height, glm::vec3 position, std::shared_ptr<Renderer::Model> model) {
		this->m_name = "Floor";
		this->m_shader = shader;
		this->m_model = model;

		m_position = position;
		m_scale = glm::vec3(width, 0.1, height);
		m_transform = getTransformMatrix();
	}


	Floor::~Floor()
	{
	}

	void Floor::update(double time) {

	}

	void Floor::render(std::shared_ptr<Renderer::Renderer> renderer) {
				
		renderer->startShader(m_shader);

		renderer->drawModel(m_model, m_transform);

		renderer->stopShader();

	}
}