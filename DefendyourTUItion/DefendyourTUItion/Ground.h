#pragma once
#include "GameObject.h"
#include "Floor.h"

namespace GameObject {
	class Ground
		: public GameObject
	{
	public:
		Ground(GLuint shader, GLint width, GLint height);
		~Ground();

		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
	
	private: 
		std::vector<std::shared_ptr<Floor>> m_floorTiles;
		GLint m_tileWidth = 100, m_tileHeight = 100;
	};
}

