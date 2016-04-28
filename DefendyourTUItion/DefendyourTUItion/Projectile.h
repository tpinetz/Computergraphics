#pragma once
#include "GameObject.h"
#include "Model.h"
#include "ObjectLoader.hpp"
#include "FormattingHelper.h"

namespace GameObject {
	
class Projectile :
		public GameObject
	{
	private:
		void initModel();
	public:
		Projectile();
		Projectile(GLuint shader, glm::vec3 position, glm::vec3 scale, glm::vec3 direction);
		~Projectile();
		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
	private:
		static GLfloat m_modelVertices[];

		glm::vec3 m_direction;
		GLuint m_shader;
		GLuint m_vertexBuffer;
		GLuint m_textureBuffer;
		GLuint m_vao;
		std::shared_ptr<Renderer::Model> m_model;

		std::string m_modelString = "../Assets/Model/Floor/Floor.obj";
		std::string m_textureString = "../Assets/Textures/ground.jpg";

		bool m_active;
		GLfloat movementSpeed = 0.05f;
	};

}