#pragma once
#include "Model.h"
#include "Renderer.h"
//#include "ObjectLoader.hpp"
#include "TextureHelper.h"
#include "DynamicModelLoader.h"
//#include "ModelLoader.h"
#include "FormattingHelper.h"
#include "PhysicsObject.h"


namespace GameObject{

	class Enemy
	: public PhysicsObject
	{
	public:
		static std::string m_typeName;
		Enemy(std::string name, glm::vec3 position, GLuint shader, DynamicModelLoader& mod);
		~Enemy();

		void update(double time);
		void render(std::shared_ptr<Renderer::Renderer> renderer);
		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) ;

		void handlePhysicsCollision(PhysicsObject* otherObject);
		inline bool isDead() {
			return m_dead;
		}
		inline bool isActive() {
			return !m_dead;
		}
	private:
		enum state{ ENEMY_WALKING, ENEMY_BEGIN_DYING, ENEMY_DYING, ENEMY_DEAD } m_actualState;
		GLfloat m_interVelocity, m_interpolvalue; //velocity and actual value of interpolation
		GLuint m_frame1, m_frame2; //frames to be displayed
		GLuint m_startWalk, m_endWalk; //start and end frames for walking
		GLuint m_startDead, m_endDead;  //start and end frames for dead

		GLfloat movementSpeed = 0.001;
		GLuint m_shader;
		//std::string m_modelString = "../Assets/Model/nanosuit/nanosuit.obj";
		DynamicModelLoader mod;

		bool m_dead = false;
	};
}

