#pragma once
#include "MainHeaders.h"
#include "LinearMath\btVector3.h"
#include "glm\vec3.hpp"
#include "Renderer.h"

namespace GameObject {
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void update(double time);
		virtual void render(std::shared_ptr<Renderer::Renderer> renderer);

		std::string getName();
		bool operator==(GameObject& rhs) {
			return m_name == rhs.m_name;
		}
	protected:
		std::string m_name;
		glm::vec3 m_position;
	};
}
