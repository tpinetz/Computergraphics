#include "GameObjectManager.h"

namespace GameObjectManager {
	GameObjectManager::GameObjectManager()
	{
	}


	GameObjectManager::~GameObjectManager()
	{
		this->m_gameObjectList.clear();
	}

	void GameObjectManager::addObject(std::shared_ptr<GameObject::GameObject> gameObject) {
		this->m_gameObjectList.push_back(gameObject);
	}

	void GameObjectManager::removeObject(GameObject::GameObject gameObject) {
		for (auto it = m_gameObjectList.begin(); it != m_gameObjectList.end(); it++) {
			if (*(it->get()) == gameObject) {
				m_gameObjectList.erase(it);
				return;
			}
		}
		
		std::cerr << "Tried to remove Gameobject: %s" << gameObject.getName() << std::endl << "Failed in the process." << std::endl;
	}

	void GameObjectManager::update(double deltaTime) {
		for (auto gameObject : this->m_gameObjectList) {
			gameObject.get()->update(deltaTime);
		}
	}

	void GameObjectManager::render() {
		for (auto gameObject : this->m_gameObjectList) {
			gameObject.get()->render();
		}
	}
}