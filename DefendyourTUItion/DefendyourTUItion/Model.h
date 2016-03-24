#pragma once
#include "MainHeaders.h"
#include "glm\vec3.hpp"

namespace Renderer {

	class Model
	{
	public:
		Model();
		Model(std::shared_ptr<GLuint> vertexBuffer);
		Model(std::shared_ptr<GLuint> vertexBuffer, int triangles);
		~Model();

		inline std::shared_ptr<GLuint> getVertexBuffer() {
			return m_vertexBuffer;
		}

		inline int getTriangleCount() {
			return m_triangles;
		}

	private:
		GLuint m_vertexArrayID;
		std::shared_ptr<GLuint> m_vertexBuffer;
		int m_triangles;
	};

}