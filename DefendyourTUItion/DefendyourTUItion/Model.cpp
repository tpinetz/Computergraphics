#include "Model.h"

namespace Renderer {

	Model::Model() 
		: Model(NULL)
	{
	}

	Model::Model(GLuint vao)
		: Model(vao, 0) {
	}

	Model::Model(GLuint vao, int triangles) 
		: Model(vao, triangles, false) {

	}

	Model::Model(GLuint vao, int triangles, bool indices) {
		m_vao = vao;
		m_triangles = triangles;
		m_indices = indices;

	}


	Model::~Model()
	{
	}

}