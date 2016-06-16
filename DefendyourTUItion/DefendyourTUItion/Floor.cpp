#include "Floor.h"

namespace GameObject {

	Floor::Floor(GLuint shader, GLfloat width, GLfloat height, glm::vec3 position, std::shared_ptr<Renderer::Model> model, std::shared_ptr<Renderer::Frustum> frustum) {
		this->m_name = "Floor";
		this->m_shader = shader;
		this->m_model = model;
		this->m_frustum = frustum;

		m_position = position;
		m_scale = glm::vec3(width, 0.1, height);
		m_transform = getTransformMatrix();
	}


	Floor::~Floor()
	{
	}

	void Floor::update(double time) {

	}

	int Floor::render(std::shared_ptr<Renderer::Renderer> renderer) {
		m_frustum->updateFrustum(m_transform);
		if (!m_frustum->CubeInFrustum(0.0f, 0.0f, 0.0f, 1.0f)) {
			return 0;
		}
				
		renderer->startShader(m_shader);

		renderer->drawModel(m_model, m_transform);

		renderer->stopShader();

		return 1;

	}
	
	void Floor::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		renderer->startShader(shader);
		renderer->drawShadow(m_model, m_transform);
		renderer->stopShader();
	}
}