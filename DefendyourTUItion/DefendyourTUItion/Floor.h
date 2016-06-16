#pragma once
#include "GameObject.h"
#include "MainHeaders.h"
#include "btBulletDynamicsCommon.h"
#include "TextureHelper.h"
#include "ObjectLoader.hpp"
#include "Mesh.h"

namespace GameObject {

	class Floor :
		public GameObject
	{

	public:
		Floor(GLuint shader, GLfloat width, GLfloat height, 
			glm::vec3 position, std::shared_ptr<Renderer::Model> model, std::shared_ptr<Renderer::Frustum> frustum);
		~Floor();
		void update(double time);
		int render(std::shared_ptr<Renderer::Renderer> renderer);
		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader);
	private:
		std::shared_ptr<Renderer::Model> m_model;
		std::shared_ptr<btCollisionShape> m_groundShape;
		std::shared_ptr<Renderer::Frustum> m_frustum;
		GLuint m_shader;
		glm::mat4 m_transform;

	};

}