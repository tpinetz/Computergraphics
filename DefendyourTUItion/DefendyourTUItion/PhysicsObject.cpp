#include "PhysicsObject.h"

namespace GameObject {

	PhysicsObject::PhysicsObject()
	{
	}


	PhysicsObject::~PhysicsObject()
	{
	}

	void PhysicsObject::setPhysicsPosition(glm::vec3 position) {
		btTransform trans;
		m_rigidBody->getMotionState()->getWorldTransform(trans);
		trans.setOrigin(btVector3(position.x, position.y, position.z));
	}

	void PhysicsObject::initPhysics(glm::vec3 position, std::shared_ptr<btCollisionShape> shape) {
		m_shape = shape;
		m_motionState = std::shared_ptr<btDefaultMotionState>(
			new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1),
			btVector3(position.x, position.y, position.z)))
			);

		m_fallInertia = btVector3(0, 0, 0);
		m_shape->calculateLocalInertia(m_mass, m_fallInertia);


		btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
			m_mass,
			m_motionState.get(),
			m_shape.get(),
			m_fallInertia);
		m_rigidBody = std::shared_ptr<btRigidBody>(new btRigidBody(rigidBodyCI));
	}
}