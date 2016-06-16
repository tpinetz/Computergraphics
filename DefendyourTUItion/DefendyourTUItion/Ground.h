#pragma once
#include "GameObject.h"
#include "Floor.h"
#include "btBulletDynamicsCommon.h"
#include "PhysicsWorld.h"
#include "ModelLoaderHelper.h"
#include "FormattingHelper.h"

namespace GameObject {
	class Ground
		: public PhysicsObject
	{
	public:
		Ground(GLuint shader, GLint width, GLint height, std::shared_ptr<Renderer::Frustum> frustum);
		~Ground();

		void update(double time);
		int render(std::shared_ptr<Renderer::Renderer> renderer);

		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader);

		void handlePhysicsCollision(PhysicsObject* otherObject);

		inline bool isActive() {
			return true;
		}
	private: 
		std::vector<std::shared_ptr<Floor>> m_floorTiles;
		GLint m_tileWidth = 25, m_tileHeight = 25;
		

		// Tile Information

		std::string m_modelString = "../Assets/Model/Floor/Floor.obj";
		std::string m_colorTextureString = "../Assets/Textures/ground01.jpg";
		std::string m_textureString = "../Assets/Textures/ground01b.jpg";
		std::string m_textureSpecString = "../Assets/Textures/ground01s.jpg";

		GLuint m_vertexBuffer;
		GLuint m_textureBuffer;
		GLuint m_vao;

	};
}

