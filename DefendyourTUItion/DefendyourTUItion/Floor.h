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
	private:
		void initModel();

	public:
		Floor(GLuint shader);
		Floor(GLuint shader, GLfloat width, GLfloat height, glm::vec3 position);
		~Floor();
		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
	private:
		static GLfloat m_modelVertices[];
		static GLuint m_modelIndices[];
		std::shared_ptr<Renderer::Model> m_model;
		std::shared_ptr<btCollisionShape> m_groundShape;
		GLuint m_shader;
		GLuint m_vertexBuffer;
		GLuint m_textureBuffer;
		GLuint m_vao;

		std::string m_modelString = "../Assets/Model/Floor/Floor.obj";
		std::string m_textureString = "../Assets/Textures/ground.jpg";
	};

}