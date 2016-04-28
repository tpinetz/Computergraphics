#include "Projectile.h"

namespace GameObject{

	Projectile::Projectile()
	{
	}

	Projectile::Projectile(GLuint shader, glm::vec3 position, glm::vec3 scale, glm::vec3 direction) {
		this->m_position = position;
		this->m_scale = scale;
		this->m_direction = direction;
		this->m_shader = shader;

		initModel();
	}

	Projectile::~Projectile()
	{
	}

	void Projectile::initModel() {
		std::vector<Vertex> vertices = loadOBJ(this->m_modelString.c_str());		//"monkey.obj", "cube.obj","cat.obj"

		if (vertices.empty()) {
			std::cerr << "Failed to load model Floor.";
			return;
		}

		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glGenBuffers(1, &m_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(glm::vec3) + sizeof(glm::vec2) + sizeof(glm::vec3)) * vertices.size(),
			&vertices[0], GL_STATIC_DRAW);


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),                  // stride
			(void*)0            // array buffer offset
			);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),                  // stride
			(GLvoid*)offsetof(Vertex, Normal)            // array buffer offset
			);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			sizeof(Vertex),                 // stride
			(GLvoid*)offsetof(Vertex, TexCoords)             // array buffer offset
			);

		glBindVertexArray(0);


		m_model = std::shared_ptr<Renderer::Model>(new Renderer::Model(m_vao, 12));

		m_model->addTexture(Common::TextureHelper::getInstance()->getTextureByName(
			m_textureString));
	}

	void Projectile::update(double time) {
		if (m_active) {
			this->m_position += (m_direction * movementSpeed *  (GLfloat)(time));
		}
	}

	void Projectile::render(std::shared_ptr<Renderer::Renderer> renderer) {
		if (m_active) {
			glm::mat4 transform = getTransformMatrix();
			renderer->startShader(m_shader);

			renderer->drawModel(this->m_model, transform);
			
			renderer->stopShader();
		}
	}
}
