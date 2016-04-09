#include "GameObject.h"

namespace GameObject {

	GameObject::GameObject()
	{
	}

	glm::mat4 GameObject::getTransformMatrix() {
		glm::mat4 transform;
		transform = glm::translate(transform, m_position);
		//TODO: Add Rotation.
		transform = glm::scale(transform, m_scale);

		return transform;
	}


	GameObject::~GameObject()
	{
	}

	void GameObject::update(double deltaTime) {

	}

	void GameObject::render(std::shared_ptr<Renderer::Renderer> renderer) {

	}

	std::string GameObject::getName() {
		return this->m_name;
	}
}