#pragma once

#include "MainHeaders.h"
#include "LinearMath\btVector3.h"
#include "glm\vec3.hpp"
#include "Renderer.h"

namespace GameObject {
	class GameObject
	{
	protected:
		glm::mat4 getTransformMatrix();
	public:
		GameObject();
		virtual ~GameObject();

		virtual void update(double time);
		virtual void render(std::shared_ptr<Renderer::Renderer> renderer);

		std::string getName();
		bool operator==(GameObject& rhs) {
			return m_name == rhs.m_name;
		}
		inline glm::vec3 getPosition() {
			return m_position;
		}
	protected:
		std::string m_name;
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};
}
