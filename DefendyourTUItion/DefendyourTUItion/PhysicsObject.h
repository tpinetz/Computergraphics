#pragma once
#include "GameObject.h"
#include "btBulletDynamicsCommon.h"

namespace GameObject {
	class PhysicsObject :
		public GameObject
	{
	protected:
		void initPhysics(glm::vec3 position, btCollisionShape* shape, bool ground = false);
		void initPhysics(btCollisionShape* shape, btDefaultMotionState* state, bool ground = false);
	public:
		PhysicsObject();
		~PhysicsObject();

		virtual void update(double time) = 0;
		virtual int render(std::shared_ptr<Renderer::Renderer> renderer) = 0;
		virtual void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) = 0;


		virtual void handlePhysicsCollision(PhysicsObject* otherObject) = 0;

		void setPhysicsPosition(glm::vec3 position);

		inline btRigidBody* getRigidBody() {
			return m_rigidBody;
		}

		virtual bool isActive() = 0;


	private:
		btCollisionShape* m_shape;
		btDefaultMotionState* m_motionState;
		btRigidBody* m_rigidBody;

	protected:
		btScalar m_mass = 1;
		btVector3 m_fallInertia;
		
	};

}

