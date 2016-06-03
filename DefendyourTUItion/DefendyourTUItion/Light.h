#pragma once
#include "GameObject.h"

namespace GameObject {
	class Light
		: public GameObject
	{
	public:
		Light(glm::vec3 position, GLuint shader, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
		~Light();

		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader);


		inline std::shared_ptr<Renderer::LightRenderingData> getRenderData() {
			return m_renderData;
		}
	private:
		GLuint m_shader;
		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;

		std::shared_ptr<Renderer::LightRenderingData> m_renderData;

		GLfloat m_constant = 1.0f;
		GLfloat m_linear = 0.009f;
		GLfloat m_quadratic = 0.0032f;
	};
}