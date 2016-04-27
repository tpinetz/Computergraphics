#include "Ground.h"

namespace GameObject {

	Ground::Ground(GLuint shader, GLint width, GLint height)
	{
		GLint fromWidth = width / 2;
		GLint fromHeight = height / 2;
		for (GLint i = -fromWidth; i <= fromWidth; i += m_tileWidth) {
			for (GLint j = -fromHeight; j <= fromHeight; j += m_tileHeight) {
				m_floorTiles.push_back(std::shared_ptr<Floor>(
					new Floor(shader, m_tileWidth, m_tileHeight, glm::vec3(i, -0.5, j))));
			}
		}
	}


	Ground::~Ground()
	{
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