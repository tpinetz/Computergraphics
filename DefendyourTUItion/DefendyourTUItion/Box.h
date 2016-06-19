#pragma once
#include "PhysicsObject.h"
namespace GameObject {

	class Box :
		public PhysicsObject
	{
	public:
		Box(std::shared_ptr<Renderer::Model> model, GLuint shader, glm::vec3 position, glm::vec3 scale,
			std::shared_ptr<Renderer::Frustum> frustum);
		~Box();

		void update(double time);
		int render(std::shared_ptr<Renderer::Renderer> renderer);
		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader);

		void handlePhysicsCollision(PhysicsObject* otherObject);

		inline bool isActive() {
			return true;
		}

	private:
		GLuint m_shader;
		std::shared_ptr<Renderer::Model> m_model;
		glm::mat4 m_transform;

		std::shared_ptr<Renderer::Frustum> m_frustum;
	};

}
