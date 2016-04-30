#pragma once
#include "PhysicsObject.h"
#include "Model.h"
#include "ObjectLoader.hpp"
#include "FormattingHelper.h"

namespace GameObject {
	
class Projectile :
		public PhysicsObject
	{
	public:
		static std::string m_typeName;

		Projectile();
		Projectile(GLuint shader, glm::vec3 position, glm::vec3 scale, 
			glm::vec3 direction, std::shared_ptr<Renderer::Model> model);
		~Projectile();
		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);

		void handlePhysicsCollision(PhysicsObject* otherObject);

		inline bool isActive() {
			return m_active;
		}

	private:

		glm::vec3 m_direction;
		GLuint m_shader;
		GLuint m_vertexBuffer;
		GLuint m_textureBuffer;
		GLuint m_vao;
		std::shared_ptr<Renderer::Model> m_model;

		std::string m_modelString = "../Assets/Model/Floor/Floor.obj";
		std::string m_textureString = "../Assets/Textures/ground.jpg";

		bool m_active;
		GLfloat m_force = 500.f;
		GLfloat m_lifeTime = 1000.0f;
	};

}