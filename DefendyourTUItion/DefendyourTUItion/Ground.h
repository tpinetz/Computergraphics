#pragma once
#include "GameObject.h"
#include "Floor.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicsWorld.h"

namespace GameObject {
	class Ground
		: public GameObject
	{
	private:
		std::shared_ptr<Renderer::Model> initTile(std::string modelString, std::string texture);
		void initPhysics(GLint width);
	public:
		Ground(GLuint shader, GLint width, GLint height);
		~Ground();

		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
	
		inline std::shared_ptr<btRigidBody> getRigidBody() {
			return m_rigidBody;
		}
	private: 
		std::vector<std::shared_ptr<Floor>> m_floorTiles;
		GLint m_tileWidth = 75, m_tileHeight = 75;
		
		std::shared_ptr<btCollisionShape> m_shape;
		std::shared_ptr<btDefaultMotionState> m_motionState;
		std::shared_ptr<btRigidBody> m_rigidBody;


		// Tile Information

		std::string m_modelString = "../Assets/Model/Floor/Floor.obj";
		std::string m_textureString = "../Assets/Textures/ground.jpg";

		GLuint m_vertexBuffer;
		GLuint m_textureBuffer;
		GLuint m_vao;

	};
}

