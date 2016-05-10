#include "DirectionalLight.h"

namespace GameObject {


	DirectionalLight::DirectionalLight(GLuint shader, glm::vec3 direction, glm::vec3 ambient,
		glm::vec3 diffuse, glm::vec3 specular)
	{
		this->m_name = "light";
		this->m_shader = shader;
		this->m_direction = direction;
		this->m_ambient = ambient;
		this->m_diffuse = diffuse;
		this->m_specular = specular;

		m_renderData = std::shared_ptr<Renderer::DirectionalLightRenderingData>(new Renderer::DirectionalLightRenderingData());
		m_renderData->direction = direction;
		m_renderData->ambient = ambient;
		m_renderData->diffuse = diffuse;
		m_renderData->specular = specular;
	}


	DirectionalLight::~DirectionalLight()
	{
	}

	void DirectionalLight::update(double time) {
	
	}

	void DirectionalLight::render(std::shared_ptr<Renderer::Renderer> renderer) {

	}

}