#include "GameObjectManager.h"

namespace GameObjectManager {
	GameObjectManager::GameObjectManager()
	{
	}


	GameObjectManager::~GameObjectManager()
	{
		this->m_gameObjectList.clear();
	}

	void GameObjectManager::addObject(GameObject::GameObject gameObject) {
		this->m_gameObjectList.push_back(gameObject);
	}

	void GameObjectManager::removeObject(GameObject::GameObject gameObject) {
		auto it = std::find(this->m_gameObjectList.begin(), this->m_gameObjectList.end(), gameObject);
		if (it != this->m_gameObjectList.end()) {
			this->m_gameObjectList.erase(it);
		}
		else {
			std::cerr << "Tried to remove Gameobject: %s" << gameObject.getName() << std::endl << "Failed in the process." << std::endl;
		}
	}

	void GameObjectManager::update(double deltaTime) {
		for (auto gameObject : this->m_gameObjectList) {
			gameObject.update(deltaTime);
		}
	}

	void GameObjectManager::render() {
		for (auto gameObject : this->m_gameObjectList) {
			gameObject.render();
		}
	}
}