#include "Ground.h"

namespace GameObject {

	Ground::Ground(GLuint shader, GLint width, GLint height)
	{
		GLint fromWidth = width / 2;
		GLint fromHeight = height / 2;

		try {

			auto model = initTile(m_modelString, m_textureString);

			for (GLint i = -fromWidth; i <= fromWidth; i += m_tileWidth) {
				for (GLint j = -fromHeight; j <= fromHeight; j += m_tileHeight) {
					m_floorTiles.push_back(std::shared_ptr<Floor>(
						new Floor(shader, m_tileWidth, m_tileHeight, glm::vec3(i, 0, j), model)));
				}
			}

			initPhysics(width);
		}
		catch (exception e) {
			std::cerr << "Failed to create ground" << std::endl;
		}

		

	}

	std::shared_ptr<Renderer::Model> Ground::initTile(std::string modelString, std::string texture) {
		std::vector<Vertex> vertices = loadOBJ(modelString.c_str());		//"monkey.obj", "cube.obj","cat.obj"

		if (vertices.empty()) {
			std::cerr << "Failed to load model Floor." << std::endl;
			throw new exception();
		}

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3) + sizeof(glm::vec2) + sizeof(glm::vec3)) * vertices.size(),
			&vertices[0], GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),                  // stride
			(void*)0            // array buffer offset
			);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),                  // stride
			(GLvoid*)offsetof(Vertex, Normal)            // array buffer offset
			);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),                 // stride
			(GLvoid*)offsetof(Vertex, TexCoords)             // array buffer offset
			);

		glBindVertexArray(0);


		auto model = std::shared_ptr<Renderer::Model>(new Renderer::Model(m_vao, 12));

		model->addTexture(Common::TextureHelper::getInstance()->getTextureByName(
			texture));

		return model;
	}

	void Ground::initPhysics(GLint width) {
		m_shape = std::shared_ptr<btCollisionShape>(new btStaticPlaneShape(btVector3(0, 1, 0), 0));
		m_motionState = std::shared_ptr<btDefaultMotionState>(
			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0))));

		btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo(0,
			m_motionState.get(),
			m_shape.get(), btVector3(0, 0, 0));

		m_rigidBody = std::shared_ptr<btRigidBody>(new btRigidBody(rigidBodyInfo));
	}


	Ground::~Ground()
	{
		glDeleteBuffers(1, &m_vertexBuffer);
		glDeleteBuffers(1, &m_textureBuffer);
		glDeleteVertexArrays(1, &m_vao);
		m_floorTiles.clear();
	}

	void Ground::update(double time) {
		for (auto floorTile : m_floorTiles) {
			floorTile->update(time);
		}
	}
	
	void Ground::render(std::shared_ptr<Renderer::Renderer> renderer) {
		for (auto floorTile : m_floorTiles) {
			floorTile->render(renderer);
		}
	}
}