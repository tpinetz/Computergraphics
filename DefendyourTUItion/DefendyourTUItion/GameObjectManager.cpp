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


	void GameObjectManager::addObjectFront(std::shared_ptr<GameObject::GameObject> gameObject) {
		this->m_gameObjectList.insert(this->m_gameObjectList.begin(), gameObject);
	}

	void GameObjectManager::removeObject(GameObject::GameObject& gameObject) {
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
			gameObject->update(deltaTime);
		}
	}

	void GameObjectManager::render(std::shared_ptr<Renderer::Renderer> renderer) {
		for (auto gameObject : this->m_gameObjectList) {
			gameObject->render(renderer);
		}
	}


	void GameObjectManager::renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) {
		for (auto gameObject : this->m_gameObjectList) {
			gameObject->renderShadows(renderer, shader);
		}
	}
}