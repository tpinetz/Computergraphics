#pragma once
#include "GameObject.h"

namespace GameObject {
	class Projectile :
		public GameObject
	{
	public:
		Projectile();
		Projectile(glm::vec3 position, glm::vec3 scale);
		~Projectile();
		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
	private:
		static GLfloat m_modelVertices[];
	};

}