#include "Floor.h"

namespace GameObject {

	GLfloat Floor::m_modelVertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 

		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 
		-0.5f, -0.5f, 0.5f, -0.0f, 0.0f, 
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 

		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 

		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 
	};


	Floor::Floor(GLuint shader)
	{
		this->m_name = "Floor";
		this->m_shader = shader;

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


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(GLvoid*)(3 * sizeof(GLfloat))            // array buffer offset
			);

		glBindVertexArray(0);


		m_model = std::shared_ptr<Renderer::Model>(new Renderer::Model(vao, 12));

		m_model->addTexture(Common::TextureHelper::getInstance()->getTextureByName(
			"../Assets/Textures/ground.jpg"));

		m_position = glm::vec3(0, -1, 0);
		m_scale = glm::vec3(1000, 0.1, 1000);
	}

	void Floor::update(double time) {

	}

	void Floor::render(std::shared_ptr<Renderer::Renderer> renderer) {


		glm::mat4 transform = getTransformMatrix();
		
		renderer->startShader(m_shader);

		renderer->drawModel(m_model, transform);

		renderer->stopShader();

	}
}