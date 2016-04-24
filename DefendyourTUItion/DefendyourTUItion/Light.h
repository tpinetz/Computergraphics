#pragma once
#include "GameObject.h"

namespace GameObject {
	class Light
		: public GameObject
	{
	public:
		Light(glm::vec3 position, GLuint shader, GLfloat lightStrength);
		~Light();

		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);

		inline std::shared_ptr<Renderer::LightRenderingData> getRenderData() {
			return m_renderData;
		}
	private:
		GLuint m_shader;
		GLfloat m_lightStrength;

		std::shared_ptr<Renderer::LightRenderingData> m_renderData;
	};
}