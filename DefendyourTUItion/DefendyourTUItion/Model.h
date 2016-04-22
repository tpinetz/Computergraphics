#pragma once
#include "MainHeaders.h"
#include "glm\vec3.hpp"

namespace Renderer {

	class Model
	{
	public:
		Model();
		Model(GLuint vao);
		Model(GLuint vao, int triangles);
		Model(GLuint vao, int triangles, bool indices);
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
		GLuint m_vertexArrayID;
		GLuint m_vao;
		int m_triangles;
		bool m_indices;
		std::shared_ptr<std::vector<GLuint>> m_textures;
	};

}