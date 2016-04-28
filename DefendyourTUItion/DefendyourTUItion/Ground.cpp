#include "Ground.h"

namespace GameObject {

	Ground::Ground(GLuint shader, GLint width, GLint height)
	{
		GLint fromWidth = width / 2;
		GLint fromHeight = height / 2;

		try {

			auto model = Common::ModelLoaderHelper::getInstance()
				->getTextureModel(m_modelString, m_textureString);

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