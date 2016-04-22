#pragma once
#include "GameObject.h"
#include "MainHeaders.h"
#include "btBulletDynamicsCommon.h"
#include "TextureHelper.h"

namespace GameObject {

	class Floor :
		public GameObject
	{
	private:
		void initModel();

	public:
		Floor(GLuint shader);
		~Floor();
		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
	private:
		static GLfloat m_modelVertices[];
		static GLuint m_modelIndices[];
		std::shared_ptr<Renderer::Model> m_model;
		std::shared_ptr<btCollisionShape> m_groundShape;
		GLuint m_shader;
	};

}