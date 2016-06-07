#include "PhysicsObject.h"

namespace GameObject {

	PhysicsObject::PhysicsObject()
	{
	}


	PhysicsObject::~PhysicsObject()
	{
		delete m_motionState;
		delete m_rigidBody;
		delete m_shape;
	}

	void PhysicsObject::setPhysicsPosition(glm::vec3 position) {
		btTransform transform = m_rigidBody->getCenterOfMassTransform();
		transform.setOrigin(btVector3(position.x, position.y, position.z));
		m_rigidBody->setCenterOfMassTransform(transform);
	}

	void PhysicsObject::initPhysics(glm::vec3 position, btCollisionShape* shape, bool ground ){
		btDefaultMotionState* state =
			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
			btVector3(position.x, position.y, position.z)));

		initPhysics(shape, state, ground);
	}

	void PhysicsObject::initPhysics(btCollisionShape* shape, btDefaultMotionState* state, bool ground ) {
		m_shape = shape;
		m_motionState = state;

		m_fallInertia = btVector3(0, 0, 0);
		if (!ground) {
			m_shape->calculateLocalInertia(m_mass, m_fallInertia);
		}
		

		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
			m_mass,
			state,
			m_shape,
			m_fallInertia);
		m_rigidBody = new btRigidBody(rigidBodyCI);
	}
}