#include "GameObject.h"

namespace GameObject {

	GameObject::GameObject()
	{
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