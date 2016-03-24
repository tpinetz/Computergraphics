#include "Avatar.h"

namespace Avatar{

	GLfloat Avatar::m_modelVertices[] = {
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f, 
		0.5f, 0.5f, 0.5f, 
		0.5f, 0.5f, 0.5f, 
		-0.5f, 0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f, 
		-0.5f, 0.5f, -0.5f, 
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f, 
		-0.5f, 0.5f, 0.5f, 

		0.5f, 0.5f, 0.5f, 
		0.5f, 0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, 0.5f, 
		0.5f, 0.5f, 0.5f, 

		-0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f, 
		-0.5f, -0.5f, -0.5f,

		-0.5f, 0.5f, -0.5f, 
		0.5f, 0.5f, -0.5f, 
		0.5f, 0.5f, 0.5f, 
		0.5f, 0.5f, 0.5f, 
		-0.5f, 0.5f, 0.5f, 
		-0.5f, 0.5f, -0.5f,
	};

	Avatar::Avatar(std::shared_ptr<Camera::Camera> camera)
	{
		m_name = "Avatar";
		m_camera = camera;
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);

		initModel();
	}

	void Avatar::initModel() {
		std::shared_ptr<GLuint> vertexBuffer = std::shared_ptr<GLuint>(new GLuint);

		glGenBuffers(1, vertexBuffer.get());
		glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Avatar::m_modelVertices), Avatar
			::m_modelVertices, GL_STATIC_DRAW);

		m_model = std::shared_ptr<Renderer::Model>(new Renderer::Model(vertexBuffer, 12));
	}


	Avatar::~Avatar()
	{
	}

	void Avatar::update(double deltaTime) {
		m_camera->update(deltaTime);
	}

	void Avatar::render(std::shared_ptr<Renderer::Renderer> renderer) {
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		renderer->drawModel(m_model);

		glDisableVertexAttribArray(0);
	}
}