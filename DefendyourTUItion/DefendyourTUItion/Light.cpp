#include "Light.h"

namespace GameObject {


	Light::Light(glm::vec3 position, GLuint shader, GLfloat lightStrength)
	{
		this->m_shader = shader;
		this->m_position = position;
		this->m_lightStrength = lightStrength;

		m_renderData = std::shared_ptr<Renderer::LightRenderingData>(new Renderer::LightRenderingData());
		m_renderData->position = position;
		m_renderData->lightStrength = lightStrength;
	}


	Light::~Light()
	{
	}

	void Light::update(double time) {

	}

	void Light::render(std::shared_ptr<Renderer::Renderer> renderer) {

	}

}