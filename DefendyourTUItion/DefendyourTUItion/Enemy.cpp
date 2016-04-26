#include "Enemy.h"

namespace GameObject {

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
		mod.loadModel(m_modelString.c_str());
	}

	void Enemy::update(double time) {
		GLfloat deltaTime = time;
		m_position += glm::normalize(-m_position) * movementSpeed * deltaTime;

		//std::cout << "Position of enemy (" << this->m_name << "): " << m_position.x << std::endl;

	}


	void Enemy::render(std::shared_ptr<Renderer::Renderer> renderer) {

		glm::mat4 transform = getTransformMatrix();
		renderer->startShader(m_shader);
		renderer->drawModel(mod, transform);
		renderer->stopShader();
	}
}
