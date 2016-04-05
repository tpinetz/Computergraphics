#include "PhysicsWorld.h"

namespace Physics {

	PhysicsWorld::PhysicsWorld()
	{
	}


	PhysicsWorld::~PhysicsWorld()
	{
	}

	bool PhysicsWorld::initPhysics() {
		m_broadphase = std::shared_ptr<btBroadphaseInterface>(new btDbvtBroadphase());
		m_collisionConfiguration = std::shared_ptr<
			btDefaultCollisionConfiguration>(new btDefaultCollisionConfiguration());

		m_dispatcher = std::shared_ptr
			<btCollisionDispatcher>(new btCollisionDispatcher(m_collisionConfiguration.get()));

		btGImpactCollisionAlgorithm::registerAlgorithm(m_dispatcher.get());
		m_solver = std::shared_ptr
			<btSequentialImpulseConstraintSolver>(new btSequentialImpulseConstraintSolver);

		m_world = std::shared_ptr
			<btDiscreteDynamicsWorld>(new btDiscreteDynamicsWorld(m_dispatcher.get(), 
			m_broadphase.get(),
			m_solver.get(), 
			m_collisionConfiguration.get()));

		m_world->setGravity(btVector3(0, -10, 0));

		return true;
	}

	void PhysicsWorld::runPhysics(float deltaTime) {
		m_world->stepSimulation(deltaTime);
	}

}