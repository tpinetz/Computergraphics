#pragma once
#include "GameObject.h"
namespace GameObject {

	class Podest :
		public GameObject
	{
	public:
		Podest(GLuint shader, std::shared_ptr<Renderer::Model> model, std::shared_ptr<Renderer::Frustum> frustum);
		~Podest();

		void update(double time);
		int render(std::shared_ptr<Renderer::Renderer> renderer);
		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader);

		inline void setAlpha(GLfloat alpha) {
			m_alpha = alpha;
		}
	private:
		GLuint m_shader;
		std::shared_ptr<Renderer::Frustum> m_frustum;
		std::shared_ptr<Renderer::Model> m_model;
		glm::mat4 m_transform;
		GLfloat m_alpha = 1.0f;
	};

}
