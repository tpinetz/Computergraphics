#pragma once
#include "MainHeaders.h"
#include "LinearMath\btVector3.h"

namespace GameObject {
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void update(double time);
		virtual void render();

		std::string getName();
		bool operator==(GameObject& rhs) {
			return m_name == rhs.m_name;
		}
	protected:
		std::string m_name;
	};
}
