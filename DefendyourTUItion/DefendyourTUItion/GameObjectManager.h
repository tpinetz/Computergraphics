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
		void removeObject(GameObject::GameObject& gameObject);
	
		void update(double deltaTime);
		void render(std::shared_ptr<Renderer::Renderer> renderer);

		inline std::vector<std::shared_ptr<GameObject::GameObject>>& getGameObjects() {
			return m_gameObjectList;
		}

	private:
		std::vector<std::shared_ptr<GameObject::GameObject>> m_gameObjectList;
	};

}
