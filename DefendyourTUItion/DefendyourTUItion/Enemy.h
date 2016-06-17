#pragma once
#include "Model.h"
#include "Renderer.h"
#include "TextureHelper.h"
#include "DynamicModelLoader.h"
#include "FormattingHelper.h"
#include "PhysicsObject.h"


namespace GameObject{

	class Enemy
	: public PhysicsObject
	{
	public:
		static std::string m_typeName;
		Enemy(std::string name, glm::vec3 position, GLuint shader, DynamicModelLoader& mod, std::shared_ptr<Renderer::Frustum> frustum);
		~Enemy();

		void update(double time);
		int render(std::shared_ptr<Renderer::Renderer> renderer);
		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) ;

		void handlePhysicsCollision(PhysicsObject* otherObject);
		inline bool isDead() {
			return m_dead;
		}
		inline bool isActive() {
			return !m_dead;
		}
	private:
		GLfloat movementSpeed = 2.5f;
		enum state{ ENEMY_WALKING, ENEMY_DYING, ENEMY_DEAD } m_actualState;
		GLfloat m_velocityWalk, m_velocityDead, m_interVelocity; //velocity and actual value of interpolation
		GLdouble m_dTime, m_TimeInTicks;
		GLdouble m_startWalk, m_endWalk; //start and end frames for walking
		GLdouble m_startDead, m_endDead;  //start and end frames for dead

		GLuint m_shader;
		DynamicModelLoader mod;

		bool m_dead = false;
		std::shared_ptr<Renderer::Frustum> m_frustum;
	};
}

