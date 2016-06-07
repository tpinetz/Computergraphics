#include "Ground.h"

namespace GameObject {

	Ground::Ground(GLuint shader, GLint width, GLint height)
	{
		GLint fromWidth = width / 2;
		GLint fromHeight = height / 2;

		this->m_name = "ground";

		try {
			auto model = Common::ModelLoaderHelper::getInstance()
				->getTextureModel(m_modelString, m_colorTextureString, m_textureString, m_textureSpecString);

			for (GLint i = -fromWidth; i <= fromWidth; i += 2*m_tileWidth) {
				for (GLint j = -fromHeight; j <= fromHeight; j += 2*m_tileHeight) {
					m_floorTiles.push_back(std::shared_ptr<Floor>(
						new Floor(shader, m_tileWidth, m_tileHeight, glm::vec3(i, 0, j), model)));
				}
			}

			btStaticPlaneShape* shape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);
			shape->setLocalScaling(btVector3(width, height, 1));
			btDefaultMotionState* groundMotionState = 
				new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
			this->initPhysics(shape, groundMotionState);
		}
		catch (exception e) {
			std::cerr << "Failed to create ground" << std::endl;
		}		
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


	void Ground::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		for (auto floorTile : m_floorTiles) {
			floorTile->renderShadows(renderer, shader);
		}
	}

	void Ground::handlePhysicsCollision(PhysicsObject* otherObject) {

	}
}