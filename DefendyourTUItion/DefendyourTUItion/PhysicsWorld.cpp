#include "PhysicsWorld.h"
#include "BulletCollision\CollisionDispatch\btCollisionWorld.h"

namespace Physics {


	struct btDrawingResult : public btCollisionWorld::ContactResultCallback
	{

		GameObject::PhysicsObject* objectA;
		GameObject::PhysicsObject* objectB;

		virtual	btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0Wrap, 
			int partId0, 
			int index0, 
			const btCollisionObjectWrapper* colObj1Wrap, 
			int partId1, 
			int index1)
		{

			objectA->handlePhysicsCollision(objectB);
			objectB->handlePhysicsCollision(objectA);

			return 0;
		}
	};

	PhysicsWorld::PhysicsWorld()
	{
	}

	
	void PhysicsWorld::myTickCallback(btDynamicsWorld *world, btScalar timeStep) {
		PhysicsWorld *w = static_cast<PhysicsWorld*>(world->getWorldUserInfo());
		w->myProcessCallback(timeStep);
	}

	void PhysicsWorld::myProcessCallback(btScalar timestep) {
		for (int i = 0; i < m_projectileObjects.size(); i++) {
			auto objectA = m_projectileObjects[i].get();
			if (!objectA->isActive()) continue;

			for (int j = 0; j < m_physicsEnemyObjects.size(); j++) {
				auto objectB = m_physicsEnemyObjects[j].get();

				if (objectB->isDead()) continue;
				if (!objectA->isActive()) break;
				btDrawingResult physicsCallback;

				physicsCallback.objectA = objectA;
				physicsCallback.objectB = objectB;
				
				m_world->contactPairTest(objectA->getRigidBody(),
					objectB->getRigidBody(), physicsCallback);
			}
		}

	}

	PhysicsWorld::~PhysicsWorld()
	{
	}

	void PhysicsWorld::cleanUp() {
		for (auto physicsObject : m_physicsEnemyObjects) {
			m_world->removeRigidBody(physicsObject->getRigidBody());
		}
		for (auto physicsObject : m_projectileObjects) {
			m_world->removeRigidBody(physicsObject->getRigidBody());
		}

		m_physicsEnemyObjects.clear();
		m_projectileObjects.clear();
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
		
		if (physicObject->getName().compare(GameObject::Enemy::m_typeName) == 0) {
			m_physicsEnemyObjects.push_back(std::shared_ptr<GameObject::Enemy>
				(dynamic_cast<GameObject::Enemy*>(physicObject.get())));
		}
		else if (physicObject->getName().compare(GameObject::Projectile::m_typeName) == 0) {
			m_projectileObjects.push_back(std::shared_ptr<GameObject::Projectile>
				(dynamic_cast<GameObject::Projectile*>(physicObject.get())));
		}
		
		m_world->addRigidBody(physicObject->getRigidBody());
	}

}