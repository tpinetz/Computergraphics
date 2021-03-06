#pragma once
#include "GameObject.h"


namespace GameObject {

	class SkyBox :
		public GameObject
	{
	public:
		SkyBox(GLuint shader);
		~SkyBox();

		GLuint loadCubemap(vector<const GLchar*> faces);
		void update(double time);
		int render(std::shared_ptr<Renderer::Renderer> renderer);

		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader);

	private:
		GLuint m_shader;
		std::shared_ptr<Renderer::Model> m_model;
		glm::mat4 m_transform;
		GLuint skyboxVAO, skyboxVBO;
		GLuint cubeTexture;
		vector<const GLchar*> faces;
		GLuint cubemapTexture;
	};

}
