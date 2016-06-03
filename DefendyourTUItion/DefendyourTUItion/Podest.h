#pragma once
#include "GameObject.h"

namespace GameObject {

	class Podest :
		public GameObject
	{
	public:
		Podest(GLuint shader, std::shared_ptr<Renderer::Model> model);
		~Podest();

		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader);

	
	private:
		GLuint m_shader;
		std::shared_ptr<Renderer::Model> m_model;
		glm::mat4 m_transform;
	};

}
