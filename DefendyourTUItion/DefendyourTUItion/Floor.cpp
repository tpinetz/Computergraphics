#include "Floor.h"

namespace GameObject {

	GLfloat Floor::m_modelVertices[] = {
		// front
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0,
	};

	GLuint Floor::m_modelIndices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};


	Floor::Floor()
	{
		this->m_name = "Floor";

		this->initModel();
	}


	Floor::~Floor()
	{
	}

	void Floor::initModel() {
		std::shared_ptr<GLuint> vertexBuffer = std::shared_ptr<GLuint>(new GLuint);
		GLuint vao;
		GLuint indexBuffer;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, vertexBuffer.get());
		glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Floor::m_modelVertices), 
			Floor::m_modelVertices, GL_STATIC_DRAW);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_modelIndices), m_modelIndices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		glBindVertexArray(0);


		m_model = std::shared_ptr<Renderer::Model>(new Renderer::Model(vao, 12, true));


		m_position = glm::vec3(0, -1, 0);
		m_scale = glm::vec3(1000, 0.1, 1000);
	}

	void Floor::update(double time) {

	}

	void Floor::render(std::shared_ptr<Renderer::Renderer> renderer) {


		glm::mat4 transform = getTransformMatrix();

		renderer->drawModel(m_model, transform);

	}
}