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
		void addObjectFront(std::shared_ptr<GameObject::GameObject> gameObject);
		void removeObject(GameObject::GameObject& gameObject);
	
		void update(double deltaTime);
		int render(std::shared_ptr<Renderer::Renderer> renderer);
		void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader);

		inline std::vector<std::shared_ptr<GameObject::GameObject>>& getGameObjects() {
			return m_gameObjectList;
		}

	private:
		std::vector<std::shared_ptr<GameObject::GameObject>> m_gameObjectList;
	};

}
