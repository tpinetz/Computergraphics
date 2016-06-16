#pragma once

#include "MainHeaders.h"
#include "LinearMath\btVector3.h"
#include "glm\vec3.hpp"
#include "Renderer.h"
#include "Frustum.h"

namespace GameObject {
	class GameObject
	{
	protected:
		glm::mat4 getTransformMatrix();
	public:
		GameObject();
		virtual ~GameObject();

		virtual void update(double time) = 0;
		virtual int render(std::shared_ptr<Renderer::Renderer> renderer) = 0;
		virtual void renderShadows(std::shared_ptr<Renderer::Renderer> renderer, GLuint shader) = 0;


		std::string getName();
		bool operator==(GameObject& rhs) {
			return m_name == rhs.m_name;
		}
		inline glm::vec3 getPosition() {
			return m_position;
		}
	protected:
		std::string m_name;
		glm::vec3 m_position = glm::vec3(0, 0, 0);
		glm::vec3 m_rotation = glm::vec3(0, 0, 0);
		glm::vec3 m_scale = glm::vec3(1, 1, 1);
	};
}
