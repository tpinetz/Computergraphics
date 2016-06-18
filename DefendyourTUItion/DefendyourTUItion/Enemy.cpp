#include "Enemy.h"

namespace GameObject {
	std::string Enemy::m_typeName = "Enemy";

	Enemy::~Enemy()
	{
	}

	Enemy::Enemy(std::string name, glm::vec3 position, GLuint shader, DynamicModelLoader& mod, GLfloat movementspeed, std::shared_ptr<Renderer::Frustum> frustum)
	{
		this->m_name = m_typeName;
		this->m_position = position;
		this->m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		this->m_shader = shader;
		this->mod = mod;
		this->m_frustum = frustum;
		this->m_movementSpeed = movementspeed;

		//rotate the enemy to face the objective 
		glm::vec3 pos = -glm::vec3(position.x, position.y, position.z);
		glm::vec3 a = glm::normalize(glm::cross(glm::vec3(0.0f, 0.0f, -1.0f), glm::normalize(pos)));
		m_rotation.y = glm::acos(glm::dot(glm::normalize(pos), glm::vec3(0.0f, 0.0f, -1.0f))) * 180.0f / 3.14159f;
		if (a.y < 0) m_rotation.y = 360.0f - m_rotation.y;
		m_rotation.y = m_rotation.y * 3.14159f / 180.0f;

		m_mass = 10;
		this->initPhysics(position, 
			new btBoxShape(btVector3(1.5, 1.8, 1)));


		m_startWalk = 1.0;
		m_endWalk = 13.6;
		m_startDead = 166;
		m_endDead = 173;
		m_velocityWalk = 0.5f;
		m_velocityDead = 0.5f;
		m_interVelocity = m_velocityWalk;
		m_dTime = 0;


		//Begin walking
		m_actualState = ENEMY_WALKING;
	}
	
	
	void Enemy::update(double time) {
		if (!m_dead) {
			btTransform trans = getRigidBody()->getWorldTransform();
			m_position = glm::vec3(trans.getOrigin().x(), trans.getOrigin().y(), trans.getOrigin().z());
			//std::cout << "Enemy game position: " << Common::FormattingHelper::getFormattedVectorString(m_position) << std::endl;

			glm::vec3 forceVec = glm::normalize(-m_position) * m_movementSpeed;

			getRigidBody()->setLinearVelocity(btVector3(forceVec.x, forceVec.y, forceVec.z));
		}

		m_dTime += time * m_interVelocity;

		m_TimeInTicks = m_dTime * mod.getTicksPerSecond();


		switch (m_actualState)
		{
		case ENEMY_WALKING:
			/* Move to next frame */

			if (m_TimeInTicks > m_endWalk) m_dTime = m_startWalk / mod.getTicksPerSecond();
			if (m_TimeInTicks < m_startWalk) m_dTime = m_startWalk / mod.getTicksPerSecond();
			break;
		case ENEMY_DYING:
			if (m_TimeInTicks > m_endDead){
				//keep in last frame. Stay dead
				m_actualState = ENEMY_DEAD;
				if (m_TimeInTicks > m_endDead) m_dTime = m_endDead / mod.getTicksPerSecond();
			}


			break;
		case ENEMY_DEAD:
			if (m_TimeInTicks > m_endDead) m_dTime = m_endDead / mod.getTicksPerSecond();
			break;
		default:
			break;
		}
		
	}

	void Enemy::handlePhysicsCollision(PhysicsObject* otherObject) {
		m_dead = true;

		m_dTime = m_startDead / mod.getTicksPerSecond(); //begin dead animation
		m_interVelocity = m_velocityDead;

		m_actualState = ENEMY_DYING;
	}


	int Enemy::render(std::shared_ptr<Renderer::Renderer> renderer) {
			glDisable(GL_CULL_FACE);
			glm::mat4 transform = getTransformMatrix();
			m_frustum->updateFrustum(transform);
			glm::vec3 frustumVec = m_scale;
			frustumVec.y *= 8.f;
			if (!m_frustum->CubeInFrustum(0.0f, 0.0f, 0.0f, 3.0f)) {
				return 0;
			}
			//Animate object for the given time
			mod.Animate(m_dTime);

			renderer->startShader(m_shader);

			// pass bone information transformation to shader
			GLuint count = 0;
			std::vector<glm::mat4> arr = mod.getBonesMatrix(count);

			GLint loc = glGetUniformLocation(m_shader, "gBones");
			glUniformMatrix4fv(loc, count, GL_FALSE, &(arr.data()[0][0][0]));

			renderer->drawModel(mod, transform);
			renderer->stopShader();
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			return 1;
	}

	void Enemy::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
			glm::mat4 transform = getTransformMatrix();

			//Animate object for the given time
			mod.Animate(m_dTime);
			renderer->startShader(shader);
			renderer->drawShadow(mod, transform);
			renderer->stopShader();
	}
}
