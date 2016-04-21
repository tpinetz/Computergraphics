#pragma once
#include "GameObject.h"
#include "MainHeaders.h"
#include "btBulletDynamicsCommon.h"

namespace GameObject {

	class Floor :
		public GameObject
	{
	private:
		void initModel();

	public:
		Floor();
		~Floor();
		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
	private:
		static GLfloat m_modelVertices[];
		std::shared_ptr<Renderer::Model> m_model;
		std::shared_ptr<btCollisionShape> m_groundShape;
	};

}