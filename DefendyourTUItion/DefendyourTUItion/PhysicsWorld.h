#pragma once
#include "MainHeaders.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"
#include "GameObject.h"

namespace Physics
		{

	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld();
		
		bool initPhysics();
		void runPhysics(float deltaTime);

		void addRigidBody(std::shared_ptr<btRigidBody> rigidBody);
		
		inline std::shared_ptr<btDiscreteDynamicsWorld> getPhysicWorld() {
			return m_world;
		}

	private:
		std::shared_ptr<btBroadphaseInterface> m_broadphase;
		std::shared_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
		std::shared_ptr<btCollisionDispatcher> m_dispatcher;
		std::shared_ptr<btSequentialImpulseConstraintSolver> m_solver;
		std::shared_ptr<btDiscreteDynamicsWorld> m_world;

		vector<std::shared_ptr<btRigidBody>> m_rigidBodies;

	};

}

