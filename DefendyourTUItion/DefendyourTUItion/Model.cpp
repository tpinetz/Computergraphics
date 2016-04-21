#include "Model.h"

namespace Renderer {

	Model::Model() 
		: Model(NULL)
	{
	}

	Model::Model(GLuint vao)
		: Model(vao, 0) {
		m_vao = vao;
	}

	Model::Model(GLuint vao, int triangles) {
		m_vao = vao;
		m_triangles = triangles;

	}


	Model::~Model()
	{
	}

}