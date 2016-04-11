#include "Enemy.h"

namespace GameObject {

	GLfloat Enemy::m_modelVertices[] = {
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

	Enemy::Enemy(std::string name, glm::vec3 position)
	{
		this->m_name = name;
		this->m_position = position;
		
		this->initModel();
	}


	Enemy::~Enemy()
	{
	}

	void Enemy::initModel() {
		std::shared_ptr<GLuint> vertexBuffer = std::shared_ptr<GLuint>(new GLuint);
		glGenBuffers(1, vertexBuffer.get());
		glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals; // Won't be used at the moment.
		bool res = loadOBJ("cat.obj", vertices, uvs, normals);		//"monkey.obj", "cube.obj","cat.obj"
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
		m_model = std::shared_ptr<Renderer::Model>(new Renderer::Model(vertexBuffer, vertices.size()));


		/*std::shared_ptr<GLuint> vertexBuffer = std::shared_ptr<GLuint>(new GLuint);

		glGenBuffers(1, vertexBuffer.get());
		glBindBuffer(GL_ARRAY_BUFFER, *vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Enemy::m_modelVertices),
			Enemy::m_modelVertices, GL_STATIC_DRAW);

		m_model = std::shared_ptr<Renderer::Model>(new Renderer::Model(vertexBuffer, 12)); */
	}

	void Enemy::update(double time) {
		GLfloat deltaTime = time;
		m_position += glm::normalize(-m_position) * movementSpeed * deltaTime;

		std::cout << "Position of enemy (" << this->m_name << "): " << m_position.x << std::endl;

	}


	void Enemy::render(std::shared_ptr<Renderer::Renderer> renderer) {
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		glm::mat4 transform = getTransformMatrix();

		renderer->drawModel(m_model, transform);

		glDisableVertexAttribArray(0);
	}
}
