#include "Light.h"

namespace GameObject {


	Light::Light(glm::vec3 position, GLuint shader, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
	{
		this->m_name = "light";
		this->m_shader = shader;
		this->m_position = position;
		this->m_ambient = ambient;
		this->m_diffuse = diffuse;
		this->m_specular = specular;

		m_renderData = std::shared_ptr<Renderer::LightRenderingData>(new Renderer::LightRenderingData());
		m_renderData->position = position;
		m_renderData->ambient = ambient;
		m_renderData->diffuse = diffuse;
		m_renderData->specular = specular;
		m_renderData->constant = m_constant;
		m_renderData->linear = m_linear;
		m_renderData->quadratic = m_quadratic;

	}


	Light::~Light()
	{
	}

	void Light::update(double time) {

	}

	void Light::render(std::shared_ptr<Renderer::Renderer> renderer) {

	}

}