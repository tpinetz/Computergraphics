#include "Projectile.h"

namespace GameObject{
	std::string Projectile::m_typeName = "projectile";
	GLfloat Projectile::m_particleVertexData[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	Projectile::Projectile(GLuint shader, glm::vec3 position, 
		glm::vec3 scale, glm::vec3 direction, std::shared_ptr<Renderer::Model> model, 
		std::shared_ptr<Camera::Camera> camera, std::shared_ptr<ModelLoader> particleModel, GLuint particleShader) {
		this->m_name = m_typeName;
		this->m_position = position;
		this->m_scale = scale;
		this->m_direction = direction;
		this->m_shader = shader;
		this->m_model = model;
		this->m_camera = camera;
		this->m_particleModel = particleModel;
		this->m_particleShader = particleShader;

		initPhysics(m_position, new btBoxShape(btVector3(scale.x, scale.y, scale.z)));

		glm::vec3 forceVector = m_direction * m_force;
		getRigidBody()->applyCentralForce(btVector3(forceVector.x, forceVector.y, forceVector.z));
		setUpParticles();
	}

	void Projectile::setUpParticles() {
		srand(glfwGetTime()); // initialize random seed	
		GLfloat radius = 7.5f;
		GLfloat offset = 2.50f;
		for (GLuint i = 0; i < s_MaxParticles; i++)
		{
			Particle& particle = m_particles[i];
			glm::mat4 model;
			// 1. Translation: Randomly displace along circle with radius 'radius' in range [-offset, offset]
			particle.angle = (GLfloat)i / (GLfloat)s_MaxParticles * 360.0f;
			particle.displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
			particle.pos.x = sin(particle.angle) * radius + particle.displacement;
			particle.displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
			particle.pos.y = -2.5f + particle.displacement ; // Keep height of asteroid field smaller compared to width of x and z
			particle.displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
			particle.pos.z = cos(particle.angle) * radius + particle.displacement;
			model = glm::translate(model, glm::vec3(particle.pos.x, particle.pos.y, particle.pos.z));

			// 2. Scale: Scale between 0.05 and 0.25f
			particle.scale = (rand() % 20) / 100.0f + 0.05;
			model = glm::scale(model, glm::vec3(particle.scale));

			// 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
			particle.rotation = (rand() % 360);
			particle.rotationSpeed = 0.5f;
			model = glm::rotate(model, particle.rotation, glm::vec3(0.4f, 0.6f, 0.8f));

			// 4. Now add to list of matrices
			m_particleModels[i] = model;
		}
	}

	Projectile::~Projectile()
	{
	}


	void Projectile::update(double time) {
		m_lifeTime -= time;
		if (m_active) {
			
			btTransform trans;
			getRigidBody()->getMotionState()->getWorldTransform(trans);
			m_position = glm::vec3(trans.getOrigin().getX(), 
				trans.getOrigin().getY(), 
				trans.getOrigin().getZ());

			updateParticles(time);

			if (m_lifeTime <= 0) {
				m_active = false;
			}

		}
	}

	void Projectile::updateParticles(float deltaTime) {
		GLfloat radius = 150.0f;
		GLfloat offset = 25.0f;
		for (GLuint i = 0; i < s_MaxParticles; i++)
		{
			Particle& particle = m_particles[i];
			glm::mat4 model;
			model = glm::translate(model, m_scale + glm::vec3(particle.pos.x +  m_position.x, particle.pos.y + m_position.y, particle.pos.z + m_position.z));

			// 2. Scale: Scale between 0.05 and 0.25f
			model = glm::scale(model, glm::vec3(particle.scale));

			// 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
			particle.rotation = (particle.rotation + particle.rotationSpeed * deltaTime) ;
			if (particle.rotation > 360.0f) {
				particle.rotation -= 360.0f;
			}
			model = glm::rotate(model, particle.rotation, glm::vec3(0.4f, 0.6f, 0.8f));

			// 4. Now add to list of matrices
			m_particleModels[i] = model;
		}
	}
	

	void Projectile::render(std::shared_ptr<Renderer::Renderer> renderer) {
		if (m_active) {
			glm::mat4 transform = getTransformMatrix();
			renderer->startShader(m_shader);

			renderer->drawModel(this->m_model, transform);
			
			renderer->stopShader();
			renderParticles(renderer);
		}
	}

	void Projectile::renderParticles(std::shared_ptr<Renderer::Renderer> renderer) {
		for (size_t i = 0; i < s_MaxParticles; i++) {
			for (auto& mesh : m_particleModel->getModel()) {
				GLuint vao = mesh.getVAO();
				GLuint buffer;
				glBindVertexArray(vao);
				glGenBuffers(1, &buffer);
				glBindBuffer(GL_ARRAY_BUFFER, buffer);
				glBufferData(GL_ARRAY_BUFFER, s_MaxParticles * sizeof(glm::mat4), &m_particleModels[0], GL_STATIC_DRAW);
				// Vertex Attributes
				GLsizei vec4Size = sizeof(glm::vec4);
				glEnableVertexAttribArray(3);
				glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)0);
				glEnableVertexAttribArray(4);
				glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(vec4Size));
				glEnableVertexAttribArray(5);
				glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(2 * vec4Size));
				glEnableVertexAttribArray(6);
				glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (GLvoid*)(3 * vec4Size));

				glVertexAttribDivisor(3, 1);
				glVertexAttribDivisor(4, 1);
				glVertexAttribDivisor(5, 1);
				glVertexAttribDivisor(6, 1);

				glBindVertexArray(0);
			}

			renderer->startShader(m_particleShader);
			renderer->drawParticles(*m_particleModel, m_particleModels[i], s_MaxParticles);
			renderer->stopShader();
		}


	}

	void Projectile::handlePhysicsCollision(PhysicsObject* otherObject) {
		m_active = false;
	}
}
