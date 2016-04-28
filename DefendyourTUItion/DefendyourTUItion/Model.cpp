#include "Model.h"

namespace Renderer {


	Model::Model(GLuint vao, GLuint vertexBuffer, int triangles)
		: Model(vao, vertexBuffer, triangles, false) {

	}

	Model::Model(GLuint vao, GLuint vertexBuffer, int triangles, bool indices) {
		m_vao = vao;
		m_triangles = triangles;
		m_indices = indices;
		m_vertexBuffer = vertexBuffer;

		m_textures = std::shared_ptr<std::vector<GLuint>>(new std::vector<GLuint>());

	}


	Model::~Model()
	{
		glDeleteBuffers(1, &m_vertexBuffer);
		glDeleteVertexArrays(1, &m_vao);
	}

}