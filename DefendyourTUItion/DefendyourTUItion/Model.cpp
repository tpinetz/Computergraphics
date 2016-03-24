#include "Model.h"

namespace Renderer {

	Model::Model() 
		: Model(NULL)
	{
	}

	Model::Model(std::shared_ptr<GLuint> vertexBuffer)
		: Model(vertexBuffer, 0) {
		m_vertexBuffer = vertexBuffer;
	}

	Model::Model(std::shared_ptr<GLuint> vertexBuffer, int triangles) {
		m_vertexBuffer = vertexBuffer;
		m_triangles = triangles;

	}


	Model::~Model()
	{
	}

}