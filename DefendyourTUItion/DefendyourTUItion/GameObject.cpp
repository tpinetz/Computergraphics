#include "GameObject.h"

namespace GameObject {

	GameObject::GameObject()
	{
	}

	glm::mat4 GameObject::getTransformMatrix() {
		glm::mat4 transform = glm::mat4();
		transform = glm::translate(transform, m_position);
		transform = glm::rotate(transform, m_rotation.x, glm::vec3(1.f, 0.f, 0.f));
		transform = glm::rotate(transform, m_rotation.y, glm::vec3(0.f, 1.f, 0.f));
		transform = glm::rotate(transform, m_rotation.z, glm::vec3(0.f, 0.f, 1.f));
		transform = glm::scale(transform, m_scale);

		return transform;
	}


	GameObject::~GameObject()
	{
	}

	std::string GameObject::getName() {
		return this->m_name;
	}
}