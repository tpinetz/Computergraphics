#pragma once
#include "MainHeaders.h"
#include "glm\vec3.hpp"

namespace Renderer {

	class Model
	{
	public:
		Model(GLuint vao, GLuint vertexBuffer, int triangles);
		Model(GLuint vao, GLuint vertexBuffer, int triangles , bool indices);
		~Model();

		inline GLuint getVAO() {
			return m_vao;
		}

		inline int getTriangleCount() {
			return m_triangles;
		}

		inline bool getHasIndices() {
			return m_indices;
		}

		inline void addTexture(GLuint texture) {
			m_textures->push_back(texture);
		}

		inline std::shared_ptr<std::vector<GLuint>> getTextures() {
			return m_textures;
		}

	private:
		GLuint m_vao;
		GLuint m_vertexBuffer;
		int m_triangles;
		bool m_indices;
		std::shared_ptr<std::vector<GLuint>> m_textures;
	};

}