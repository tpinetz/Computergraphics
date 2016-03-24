#pragma once
#include "MainHeaders.h"
#include "GameObject.h"

namespace GameObjectManager
{
	class GameObjectManager
	{
	public:
		GameObjectManager();
		~GameObjectManager();

		void addObject(std::shared_ptr<GameObject::GameObject> gameObject);
		void removeObject(GameObject::GameObject gameObject);
	
		void update(double deltaTime);
		void render();

	private:
		std::vector<std::shared_ptr<GameObject::GameObject>> m_gameObjectList;
	};

}
