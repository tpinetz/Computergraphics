#pragma once
#include "MainHeaders.h"
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btCollisionWorld.h"
#include "BulletCollision\Gimpact\btGImpactCollisionAlgorithm.h"
#include "LinearMath\btVector3.h"
#include "glm\vec3.hpp"
#include "Enemy.h"
#include "Projectile.h"
#include "PhysicsObject.h"

namespace Physics
		{

	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld();
		static void myTickCallback(btDynamicsWorld *world, btScalar timeStep);
		
		bool initPhysics();
		void runPhysics(float deltaTime);

		void addPhysicsObject(std::shared_ptr<GameObject::PhysicsObject> physicObject);
		
		inline std::shared_ptr<btDiscreteDynamicsWorld> getPhysicWorld() {
			return m_world;
		}

		void myProcessCallback(btScalar timestep);
		inline void setGravity(btVector3& gravity) {
			m_world->setGravity(gravity);
		}

		void cleanUp();

	private:
		std::shared_ptr<btBroadphaseInterface> m_broadphase;
		std::shared_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
		std::shared_ptr<btCollisionDispatcher> m_dispatcher;
		std::shared_ptr<btSequentialImpulseConstraintSolver> m_solver;
		std::shared_ptr<btDiscreteDynamicsWorld> m_world;

		vector<std::shared_ptr<GameObject::PhysicsObject>> m_physicsEnemyObjects;
		vector<std::shared_ptr<GameObject::PhysicsObject>> m_projectileObjects;

	};

}

