#include "PhysicsWorld.h"

namespace Physics {

	PhysicsWorld::PhysicsWorld()
	{
	}

	
	void PhysicsWorld::myTickCallback(btDynamicsWorld *world, btScalar timeStep) {
		PhysicsWorld *w = static_cast<PhysicsWorld*>(world->getWorldUserInfo());
		w->myProcessCallback(timeStep);
	}

	void PhysicsWorld::myProcessCallback(btScalar timestep) {
		int numManifolds = m_world->getDispatcher()->getNumManifolds();
		for (int i = 0; i<numManifolds; i++)
		{
			btPersistentManifold* contactManifold = m_world->getDispatcher()->getManifoldByIndexInternal(i);
			const btCollisionObject* obA = (contactManifold->getBody0());
			const btCollisionObject* obB = (contactManifold->getBody1());
			btRigidBody* rigidBody;
			

			int numContacts = contactManifold->getNumContacts();
			for (int j = 0; j<numContacts; j++)
			{
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
				if (pt.getDistance()<0.f)
				{
					const btVector3& ptA = pt.getPositionWorldOnA();
					const btVector3& ptB = pt.getPositionWorldOnB();
					const btVector3& normalOnB = pt.m_normalWorldOnB;
				}
			}
		}

	}

	PhysicsWorld::~PhysicsWorld()
	{
		for (auto physicsObject : m_physicsObjects) {
			m_world->removeRigidBody(physicsObject->getRigidBody().get());
		}
	}

	bool PhysicsWorld::initPhysics() {
		m_broadphase = std::shared_ptr<btBroadphaseInterface>(new btDbvtBroadphase());
		m_collisionConfiguration = std::shared_ptr<
			btDefaultCollisionConfiguration>(new btDefaultCollisionConfiguration());

		m_dispatcher = std::shared_ptr
			<btCollisionDispatcher>(new btCollisionDispatcher(m_collisionConfiguration.get()));

		//btGImpactCollisionAlgorithm::registerAlgorithm(m_dispatcher.get());
		m_solver = std::shared_ptr
			<btSequentialImpulseConstraintSolver>(new btSequentialImpulseConstraintSolver);

		m_world = std::shared_ptr
			<btDiscreteDynamicsWorld>(new btDiscreteDynamicsWorld(m_dispatcher.get(), 
			m_broadphase.get(),
			m_solver.get(), 
			m_collisionConfiguration.get()));

		m_world->setGravity(btVector3(0, -2, 0));
		m_world->setInternalTickCallback(PhysicsWorld::myTickCallback, static_cast<void *>(this), true);

		return true;
	}

	void PhysicsWorld::runPhysics(float deltaTime) {
		m_world->stepSimulation(deltaTime);
	}

	void PhysicsWorld::addPhysicsObject(std::shared_ptr<GameObject::PhysicsObject> physicObject) {
		m_physicsObjects.push_back(physicObject);
		m_world->addRigidBody(physicObject->getRigidBody().get());
	}

}