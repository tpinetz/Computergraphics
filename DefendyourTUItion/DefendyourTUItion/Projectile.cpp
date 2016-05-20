#include "Projectile.h"

namespace GameObject{
	std::string Projectile::m_typeName = "projectile";
	GLfloat Projectile::m_particleVertexData[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	Projectile::Projectile()
	{
	}

	Projectile::Projectile(GLuint shader, glm::vec3 position, 
		glm::vec3 scale, glm::vec3 direction, std::shared_ptr<Renderer::Model> model, 
		std::shared_ptr<Camera::Camera> camera) {
		this->m_name = m_typeName;
		this->m_position = position;
		this->m_scale = scale;
		this->m_direction = direction;
		this->m_shader = shader;
		this->m_model = model;
		this->m_camera = camera;

		initPhysics(m_position, new btBoxShape(btVector3(scale.x, scale.y, scale.z)));

		glm::vec3 forceVector = m_direction * m_force;
		getRigidBody()->applyCentralForce(btVector3(forceVector.x, forceVector.y, forceVector.z));
		setUpParticles();
	}

	void Projectile::setUpParticles() {
		for (int i = 0; i < s_MaxParticles; i++) {
			Particle& part = m_ParticlesContainer[i];
			part.pos.x = m_position.x;
			part.pos.y = m_position.y;
			part.pos.z = m_position.z;
		}



		glGenBuffers(1, &billboard_vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_particleVertexData), m_particleVertexData, GL_STATIC_DRAW);


		glGenBuffers(1, &particles_position_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		// Initialize with empty (NULL) buffer : it will be updated later, each frame.
		glBufferData(GL_ARRAY_BUFFER, s_MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

		glGenBuffers(1, &particles_color_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		// Initialize with empty (NULL) buffer : it will be updated later, each frame.
		glBufferData(GL_ARRAY_BUFFER, s_MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
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
		int m_ParticlesCount = 0;
		for (int i = 0; i<s_MaxParticles; i++){

			Particle& p = m_ParticlesContainer[i]; // shortcut

			if (p.life > 0.0f){

				// Decrease life
				p.life -= deltaTime;
				if (p.life > 0.0f){

					// Simulate simple physics : gravity only, no collisions
					p.speed += glm::vec3(0.0f, -9.81f, 0.0f) * deltaTime * 0.5f;
					p.pos += p.speed * deltaTime;
					p.cameradistance = glm::length(p.pos - m_camera->getCameraPosition());
					//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta;

					// Fill the GPU buffer
					g_particule_position_size_data[4 * m_ParticlesCount + 0] = p.pos.x;
					g_particule_position_size_data[4 * m_ParticlesCount + 1] = p.pos.y;
					g_particule_position_size_data[4 * m_ParticlesCount + 2] = p.pos.z;

					g_particule_position_size_data[4 * m_ParticlesCount + 3] = p.size;

					g_particule_color_data[4 * m_ParticlesCount + 0] = p.r;
					g_particule_color_data[4 * m_ParticlesCount + 1] = p.g;
					g_particule_color_data[4 * m_ParticlesCount + 2] = p.b;
					g_particule_color_data[4 * m_ParticlesCount + 3] = p.a;

				}
				else{
					// Particles that just died will be put at the end of the buffer in SortParticles();
					p.cameradistance = -999999.0f;
				}

				m_ParticlesCount++;

			}
		}
		std::sort(&m_ParticlesContainer[0], &m_ParticlesContainer[s_MaxParticles]);


		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glBufferData(GL_ARRAY_BUFFER, s_MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_ParticlesCount * sizeof(GLfloat)* 4, g_particule_position_size_data);

		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glBufferData(GL_ARRAY_BUFFER, s_MaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_ParticlesCount * sizeof(GLubyte)* 4, g_particule_color_data);
	}
	

	void Projectile::render(std::shared_ptr<Renderer::Renderer> renderer) {
		if (m_active) {
			glm::mat4 transform = getTransformMatrix();
			renderer->startShader(m_shader);

			renderer->drawModel(this->m_model, transform);
			
			renderer->stopShader();
			renderParticles();
		}
	}

	void Projectile::renderParticles() {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
		glVertexAttribPointer(
			0, // attribute. No particular reason for 0, but must match the layout in the shader.
			3, // size
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
			);

		// 2nd attribute buffer : positions of particles' centers
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
		glVertexAttribPointer(
			1, // attribute. No particular reason for 1, but must match the layout in the shader.
			4, // size : x + y + z + size => 4
			GL_FLOAT, // type
			GL_FALSE, // normalized?
			0, // stride
			(void*)0 // array buffer offset
			);

		// 3rd attribute buffer : particles' colors
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
		glVertexAttribPointer(
			2, // attribute. No particular reason for 1, but must match the layout in the shader.
			4, // size : r + g + b + a => 4
			GL_UNSIGNED_BYTE, // type
			GL_TRUE, // normalized? *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
			0, // stride
			(void*)0 // array buffer offset
			);

		glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
		glVertexAttribDivisor(1, 1); // positions : one per quad (its center) -> 1
		glVertexAttribDivisor(2, 1); // color : one per quad -> 1

		// Draw the particules !
		// This draws many times a small triangle_strip (which looks like a quad).
		// This is equivalent to :
		// for(i in m_ParticlesCount) : glDrawArrays(GL_TRIANGLE_STRIP, 0, 4),
		// but faster.
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_ParticlesCount);
	}

	void Projectile::handlePhysicsCollision(PhysicsObject* otherObject) {
		m_active = false;
	}
}
