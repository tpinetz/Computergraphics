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

	private:
		GLuint m_vertexArrayID;
		GLuint m_vao;
		int m_triangles;
		bool m_indices;
	};

}