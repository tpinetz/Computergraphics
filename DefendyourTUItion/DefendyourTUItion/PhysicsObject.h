#pragma once
#include "GameObject.h"
#include "btBulletDynamicsCommon.h"

namespace GameObject {
	class PhysicsObject :
		public GameObject
	{
	protected:
		void initPhysics(glm::vec3 position, std::shared_ptr<btCollisionShape> shape);
	public:
		PhysicsObject();
		~PhysicsObject();

		void setPhysicsPosition(glm::vec3 position);

		virtual void update(double time) = 0;
		virtual void render(std::shared_ptr<Renderer::Renderer> renderer) = 0;

		inline std::shared_ptr<btRigidBody> getRigidBody() {
			return m_rigidBody;
		}
		
	private:
		std::shared_ptr<btCollisionShape> m_shape;
		std::shared_ptr<btDefaultMotionState> m_motionState;
		std::shared_ptr<btRigidBody> m_rigidBody;

	protected:
		btScalar m_mass = 1;
		btVector3 m_fallInertia;
	};

}

