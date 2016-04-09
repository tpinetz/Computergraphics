#pragma once
#include "GameObject.h"
#include "MainHeaders.h"

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

	};

}