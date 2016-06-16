#include "Ground.h"

namespace GameObject {

	Ground::Ground(GLuint shader, GLint width, GLint height, std::shared_ptr<Renderer::Frustum> frustum)
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
						new Floor(shader, m_tileWidth, m_tileHeight, glm::vec3(i, 0, j), model, frustum)));
				}
			}
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(0.0f, 1.0f, 0.0f));
			btCollisionShape* shape = new btStaticPlaneShape(btVector3(0, 1, 0), -1);
			m_mass = 0;
			btDefaultMotionState* groundMotionState = 
				new btDefaultMotionState(groundTransform);
			this->initPhysics(shape, groundMotionState, true);
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

		btVector3& vector = getRigidBody()->getWorldTransform().getOrigin();
//			std::cout << "PhysicsPosition Ground: " << "(" + std::to_string(vector.x()) + "," + std::to_string(vector.y())
//			+ "," + std::to_string(vector.z()) + ")" << std::endl;  
	}
	
	int Ground::render(std::shared_ptr<Renderer::Renderer> renderer) {
		int result = 0;
		for (auto floorTile : m_floorTiles) {
			result += floorTile->render(renderer);
		}
		return result;
	}


	void Ground::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		for (auto floorTile : m_floorTiles) {
			floorTile->renderShadows(renderer, shader);
		}
	}

	void Ground::handlePhysicsCollision(PhysicsObject* otherObject) {

	}
}