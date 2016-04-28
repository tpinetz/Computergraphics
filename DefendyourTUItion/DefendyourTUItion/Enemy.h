#pragma once
#include "GameObject.h"
#include "Model.h"
#include "Renderer.h"
#include "ObjectLoader.hpp"
#include "TextureHelper.h"
#include "ModelLoader.h"
#include "FormattingHelper.h"


namespace GameObject{

	class Enemy
	: public GameObject
	{
	private:
		void initPhysics(glm::vec3 position); 
	public:
		Enemy(std::string name, glm::vec3 position, GLuint shader);
		~Enemy();

		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);

		inline std::shared_ptr<btRigidBody> getRigidBody() {
			return m_rigidBody;
		}


	private:
		GLfloat movementSpeed = 0.01;
		//static GLfloat m_modelVertices[];
		std::shared_ptr<Renderer::Model> m_model;
		GLuint m_shader;
		GLuint m_vertexBuffer;
		GLuint m_vao;
		std::string m_modelString = "../Assets/Model/nanosuit/nanosuit.obj";
		ModelLoader mod;

		std::shared_ptr<btCollisionShape> m_shape;
		std::shared_ptr<btDefaultMotionState> m_motionState;
		std::shared_ptr<btRigidBody> m_rigidBody;

		btScalar m_mass = 5;
		btVector3 m_fallInertia;
	};
}

