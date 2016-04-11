#pragma once
#include "GameObject.h"
#include "Model.h"
#include "Model.h"
#include "Renderer.h"
#include "ObjectLoader.hpp"

namespace GameObject{

	class Enemy
	: public GameObject
	{
	private:
		void initModel();

	public:
		Enemy(std::string name, glm::vec3 position);
		~Enemy();

		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);


	private:
		GLfloat movementSpeed = 1;
		static GLfloat m_modelVertices[];
		std::shared_ptr<Renderer::Model> m_model;

	};
}

