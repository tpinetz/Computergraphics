#pragma once
#include "GameObject.h"

namespace GameObject {

	class DirectionalLight
		: public GameObject
	{
	public:
		DirectionalLight(GLuint shader, glm::vec3 direction, glm::vec3 ambient, 
			glm::vec3 diffuse, glm::vec3 specular);
		~DirectionalLight();

		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader);


		inline std::shared_ptr<Renderer::DirectionalLightRenderingData> getRenderData() {
			return m_renderData;
		}
	
	private:
		GLuint m_shader;
		glm::vec3 m_direction;

		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;

		std::shared_ptr<Renderer::DirectionalLightRenderingData> m_renderData;
	};
}