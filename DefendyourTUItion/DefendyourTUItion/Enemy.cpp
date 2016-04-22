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

	Enemy::Enemy(std::string name, glm::vec3 position, GLuint shader)
	{
		this->m_name = name;
		this->m_position = position;
		this->m_scale = glm::vec3(0.2f, 0.2f, 0.2f);
		this->m_shader = shader;
		
		this->initModel();
	}


	Enemy::~Enemy()
	{
	}

	void Enemy::initModel() {
		GLuint vao;
		GLuint vertexBuffer;
		GLuint vertexTextureBuffer;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec2> uvs;
		std::vector<glm::vec3> normals; // Won't be used at the moment.
		bool res = loadOBJ("cat.obj", vertices, uvs, normals);		//"monkey.obj", "cube.obj","cat.obj"

		if (!res) {
			std::cerr << "Failed to load model.";
			return;
		}


		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);


		
		glGenBuffers(1, &vertexTextureBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexTextureBuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &normals[0], GL_STATIC_DRAW);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);	

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		glBindBuffer(GL_ARRAY_BUFFER, vertexTextureBuffer);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(GLvoid*)(sizeof(GLfloat)* 3));
		glBindVertexArray(0);

		m_model = std::shared_ptr<Renderer::Model>(new Renderer::Model(vao, vertices.size()));

		m_model->addTexture(Common::TextureHelper::getInstance()->getTextureByName("../Assets/Textures/ground.jpg"));


	}

	void Enemy::update(double time) {
		GLfloat deltaTime = time;
		//m_position += glm::normalize(-m_position) * movementSpeed * deltaTime;

		//std::cout << "Position of enemy (" << this->m_name << "): " << m_position.x << std::endl;

	}


	void Enemy::render(std::shared_ptr<Renderer::Renderer> renderer) {

		glm::mat4 transform = getTransformMatrix();

		renderer->startShader(m_shader);
		renderer->drawModel(m_model, transform);
		renderer->stopShader();
	}
}
