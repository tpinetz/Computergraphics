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
		btTransform trans;
		m_rigidBody->getMotionState()->getWorldTransform(trans);
		trans.setOrigin(btVector3(position.x, position.y, position.z));
	}

	void PhysicsObject::initPhysics(glm::vec3 position, btCollisionShape* shape) {
		m_shape = shape;
		m_motionState =
			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
			btVector3(position.x, position.y, position.z)));

		m_fallInertia = btVector3(0, 0, 0);
		m_shape->calculateLocalInertia(m_mass, m_fallInertia);


		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
			m_mass,
			m_motionState,
			m_shape,
			m_fallInertia);
		m_rigidBody = new btRigidBody(rigidBodyCI);
	}
}