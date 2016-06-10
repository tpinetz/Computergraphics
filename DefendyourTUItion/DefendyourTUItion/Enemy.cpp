#include "Enemy.h"

namespace GameObject {
	std::string Enemy::m_typeName = "Enemy";

	Enemy::~Enemy()
	{
	}

	Enemy::Enemy(std::string name, glm::vec3 position, GLuint shader, DynamicModelLoader& mod)
	{
		this->m_name = m_typeName;
		this->m_position = position;
		this->m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		this->m_shader = shader;
		this->mod = mod;

		//rotate the enemy to face the objective 
		glm::vec3 pos = -glm::vec3(position.x, position.y, position.z);
		glm::vec3 a = glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), glm::normalize(pos)));
		m_rotation.y = glm::acos(glm::dot(glm::normalize(pos), glm::vec3(0.0f, 0.0f, -1.0f))) * 180.0f / 3.14159f;
		if (a.y < 0) m_rotation.y = 360.0f - m_rotation.y;
		m_rotation.y = m_rotation.y * 3.14159f / 180.0f;

		m_mass = 10;
		this->initPhysics(position, 
			new btBoxShape(btVector3(1.5, 4, 1)));


		m_startWalk = 1;
		m_endWalk = 8;
		m_startDead = 17;
		m_endDead = 26;
		m_interVelocity = 2.f;


		//Begin walking
		m_actualState = ENEMY_WALKING;
		m_frame1 = m_startWalk;
		m_frame2 = m_frame1 + 1;
		m_interpolvalue = 0;
	}
	
	
	void Enemy::update(double time) {
		if (!m_dead) {
			btTransform trans = getRigidBody()->getCenterOfMassTransform();
			m_position = glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
			//std::cout << "Enemy game position: " << Common::FormattingHelper::getFormattedVectorString(m_position) << std::endl;

			glm::vec3 forceVec = glm::normalize(-m_position) * movementSpeed *  (GLfloat)time;
			m_position += forceVec;
			setPhysicsPosition(m_position);

		}


		if (m_interpolvalue <= 0.0f)
			m_interpolvalue = 0.0f;

		m_interpolvalue += time * m_interVelocity;

		if (m_interpolvalue >= 1.0f)
		{
			switch (m_actualState)
			{
			case ENEMY_WALKING:
				/* Move to next frame */
				m_interpolvalue = 0.0f;
				m_frame1++;
				m_frame2++;

				if (m_frame2 > m_endWalk) m_frame2 = m_startWalk;
				if (m_frame1 > m_endWalk) m_frame1 = m_startWalk;
				break;
			case ENEMY_BEGIN_DYING:
				//Begin dying is ended. Now do the interpolation of dying
				m_actualState = ENEMY_DYING;
				m_frame1 = m_startDead;
				m_frame2 = m_frame1 + 1;
				m_interpolvalue = 0;

				break;
			case ENEMY_DYING:
				//keep in last frame. Stay dead
				m_interpolvalue = 0.0f;
				m_frame1++;
				m_frame2++;

				if (m_frame2 > m_endDead){
					m_actualState = ENEMY_DEAD;

					m_frame2 = m_frame1 = m_endDead;
				}


				break;
			case ENEMY_DEAD:
				m_interpolvalue = 0.0f;
				break;
			default:
				break;
			}

		}
	}

	void Enemy::handlePhysicsCollision(PhysicsObject* otherObject) {
		m_dead = true;

		m_interpolvalue = 0;
		m_frame2 = m_startDead;

		m_actualState = ENEMY_BEGIN_DYING;
	}


	void Enemy::render(std::shared_ptr<Renderer::Renderer> renderer) {
			glm::mat4 transform = getTransformMatrix();
			mod.UpdateVAO(m_frame1, m_frame2, m_interpolvalue);

			renderer->startShader(m_shader);
			renderer->drawModel(mod, transform);
			renderer->stopShader();
	}

	void Enemy::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
			glm::mat4 transform = getTransformMatrix();
			mod.UpdateVAO(m_frame1, m_frame2, m_interpolvalue);

			renderer->startShader(shader);
			renderer->drawShadow(mod, transform);
			renderer->stopShader();
	}
}
