#pragma once
#include "GameObject.h"
#include "btBulletDynamicsCommon.h"

namespace GameObject {
	class PhysicsObject :
		public GameObject
	{
	protected:
		void initPhysics(glm::vec3 position, btCollisionShape* shape);
		void initPhysics(btCollisionShape* shape, btDefaultMotionState* state);
	public:
		PhysicsObject();
		~PhysicsObject();

		virtual void update(double time) = 0;
		virtual void render(std::shared_ptr<Renderer::Renderer> renderer) = 0;

		virtual void handlePhysicsCollision(PhysicsObject* otherObject) = 0;

		void setPhysicsPosition(glm::vec3 position);

		inline btRigidBody* getRigidBody() {
			return m_rigidBody;
		}

	private:
		btCollisionShape* m_shape;
		btDefaultMotionState* m_motionState;
		btRigidBody* m_rigidBody;

	protected:
		btScalar m_mass = 1;
		btVector3 m_fallInertia;
	};

}

