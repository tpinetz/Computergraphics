#pragma once
#include "MainHeaders.h"
namespace GameObject {
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void update(double time);
		virtual void render();

		std::string getName();
		bool operator==(const GameObject& rhs) const {
			return m_name == rhs.m_name;
		}
	private:
		std::string m_name;
	};
}
