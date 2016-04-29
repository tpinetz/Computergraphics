#pragma once
#include "Model.h"
#include "Renderer.h"
#include "ObjectLoader.hpp"
#include "TextureHelper.h"
#include "ModelLoader.h"
#include "FormattingHelper.h"
#include "PhysicsObject.h"


namespace GameObject{

	class Enemy
	: public PhysicsObject
	{
	public:
		Enemy(std::string name, glm::vec3 position, GLuint shader);
		~Enemy();

		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);


	private:
		GLfloat movementSpeed = 3;
		//static GLfloat m_modelVertices[];
		std::shared_ptr<Renderer::Model> m_model;
		GLuint m_shader;
		GLuint m_vertexBuffer;
		GLuint m_vao;
		std::string m_modelString = "../Assets/Model/nanosuit/nanosuit.obj";
		ModelLoader mod;
	};
}

