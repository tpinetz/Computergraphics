#pragma once
#include "PhysicsObject.h"

namespace GameObject {
	class Obstacle :
		public PhysicsObject
	{
	public:
		Obstacle(std::shared_ptr<ModelLoader> model, GLuint shader, glm::vec3 position, glm::vec3 scale);
		~Obstacle();
	
		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer) ;
		void handlePhysicsCollision(PhysicsObject* otherObject);
		
		inline bool isActive() {
			return m_active;
		}

	private:
		std::shared_ptr<ModelLoader> m_model;
		GLuint m_shader;
		bool m_active = true;
		glm::mat4 m_transform;
	};

}